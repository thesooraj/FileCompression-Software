#include "huffman.h"

// Build frequency map from binary data
void buildFrequencyMap(const std::vector<unsigned char>& data, std::unordered_map<unsigned char, int>& freqMap) {
    for (unsigned char byte : data) {
        freqMap[byte]++;
    }
}

// Build Huffman tree
Node* buildHuffmanTree(std::unordered_map<unsigned char, int>& freqMap) {
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;

    for (auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Handle single character case
    if (pq.size() == 1) {
        Node* single = pq.top(); pq.pop();
        Node* parent = new Node('\0', single->frequency);
        parent->left = single;
        pq.push(parent);
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* parent = new Node('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    return pq.top();
}

// Build codes by traversing tree
void buildCodes(Node* root, std::string code, std::unordered_map<unsigned char, std::string>& codes) {
    if (root == nullptr) return;
    if (!root->left && !root->right) {
        codes[root->character] = code.empty() ? "0" : code;
    }
    buildCodes(root->left, code + "0", codes);
    buildCodes(root->right, code + "1", codes);
}

// Compress binary data
std::string compress(const std::vector<unsigned char>& data, std::unordered_map<unsigned char, std::string>& codes) {
    std::string compressed = "";
    for (unsigned char byte : data) {
        compressed += codes[byte];
    }
    return compressed;
}

// Decompress binary string back to data
std::vector<unsigned char> decompress(const std::string& compressed, Node* root, int originalSize) {
    std::vector<unsigned char> result;
    Node* current = root;

    for (char bit : compressed) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (!current->left && !current->right) {
            result.push_back(current->character);
            current = root;
            if ((int)result.size() == originalSize) break;
        }
    }
    return result;
}

// Clean up memory
void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}