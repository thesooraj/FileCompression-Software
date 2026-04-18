#include "huffman.h"

// Build a frequency map from the input text
// This counts how many times each character appears
void buildFrequencyMap(const std::string& text, std::unordered_map<char, int>& freqMap) {
    for (char c : text) {
        freqMap[c]++;
    }
}

// Build the Huffman tree using a priority queue
// Characters with lower frequency get longer codes
Node* buildHuffmanTree(std::unordered_map<char, int>& freqMap) {
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;

    // Create a node for each character and add to queue
    for (auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Keep combining two smallest nodes until one tree remains
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        // Create a parent node with combined frequency
        Node* parent = new Node('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    return pq.top();
}

// Build the codes for each character by traversing the tree
// Left = 0, Right = 1
void buildCodes(Node* root, std::string code, std::unordered_map<char, std::string>& codes) {
    if (root == nullptr) return;

    // If leaf node, store the code for this character
    if (!root->left && !root->right) {
        codes[root->character] = code;
    }

    buildCodes(root->left, code + "0", codes);
    buildCodes(root->right, code + "1", codes);
}

// Compress the text using the generated codes
std::string compress(const std::string& text, std::unordered_map<char, std::string>& codes) {
    std::string compressed = "";
    for (char c : text) {
        compressed += codes[c];
    }
    return compressed;
}

// Decompress the binary string back to original text
std::string decompress(const std::string& compressed, Node* root) {
    std::string result = "";
    Node* current = root;

    for (char bit : compressed) {
        // Go left for 0, right for 1
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        // If leaf node reached, we found a character
        if (!current->left && !current->right) {
            result += current->character;
            current = root;
        }
    }
    return result;
}

// Read file, compress and write to output file
void compressFile(const std::string& inputFile, const std::string& outputFile) {
    // Read input file
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cout << "Error: Cannot open input file!" << std::endl;
        return;
    }

    std::string text((std::istreambuf_iterator<char>(inFile)),
                      std::istreambuf_iterator<char>());
    inFile.close();

    // Build frequency map and huffman tree
    std::unordered_map<char, int> freqMap;
    buildFrequencyMap(text, freqMap);
    Node* root = buildHuffmanTree(freqMap);

    // Build codes and compress
    std::unordered_map<char, std::string> codes;
    buildCodes(root, "", codes);
    std::string compressed = compress(text, codes);

    // Write compressed data to output file
    std::ofstream outFile(outputFile);
    outFile << compressed;
    outFile.close();

    // Show compression stats
    std::cout << "Original size:    " << text.size() << " characters" << std::endl;
    std::cout << "Compressed size:  " << compressed.size() << " bits" << std::endl;
    std::cout << "Compression ratio: " << (float)compressed.size() / (text.size() * 8) * 100 << "%" << std::endl;
    std::cout << "Compressed file saved to: " << outputFile << std::endl;

    deleteTree(root);
}

// Read compressed file and decompress it
void decompressFile(const std::string& inputFile, const std::string& outputFile, Node* root) {
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cout << "Error: Cannot open compressed file!" << std::endl;
        return;
    }

    std::string compressed((std::istreambuf_iterator<char>(inFile)),
                            std::istreambuf_iterator<char>());
    inFile.close();

    std::string decompressed = decompress(compressed, root);

    std::ofstream outFile(outputFile);
    outFile << decompressed;
    outFile.close();

    std::cout << "Decompressed file saved to: " << outputFile << std::endl;
}

// Clean up memory by deleting the tree
void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}