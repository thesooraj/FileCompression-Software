#include "huffman.h"

int main() {
    std::cout << "====================================" << std::endl;
    std::cout << "   Huffman File Compression Tool    " << std::endl;
    std::cout << "====================================" << std::endl;

    int choice;
    std::cout << "\n1. Compress a file" << std::endl;
    std::cout << "2. Compress and Decompress a file" << std::endl;
    std::cout << "\nEnter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
        std::string inputFile, outputFile;
        std::cout << "Enter input file name: ";
        std::cin >> inputFile;
        std::cout << "Enter output file name: ";
        std::cin >> outputFile;

        // Read input file
        std::ifstream inFile(inputFile);
        if (!inFile.is_open()) {
            std::cout << "Error: Cannot open input file!" << std::endl;
            return 1;
        }
        std::string text((std::istreambuf_iterator<char>(inFile)),
                          std::istreambuf_iterator<char>());
        inFile.close();

        // Build frequency map and tree
        std::unordered_map<char, int> freqMap;
        buildFrequencyMap(text, freqMap);
        Node* root = buildHuffmanTree(freqMap);

        // Build codes
        std::unordered_map<char, std::string> codes;
        buildCodes(root, "", codes);

        // Compress
        std::string compressed = compress(text, codes);

        // Write compressed file
        std::ofstream outFile(outputFile);
        outFile << compressed;
        outFile.close();

        // Show stats
        std::cout << "\nOriginal size:     " << text.size() << " characters" << std::endl;
        std::cout << "Compressed size:   " << compressed.size() << " bits" << std::endl;
        std::cout << "Compression ratio: " << (float)compressed.size() / (text.size() * 8) * 100 << "%" << std::endl;
        std::cout << "Compressed file saved to: " << outputFile << std::endl;

        deleteTree(root);
        std::cout << "Done!" << std::endl;

    } else if (choice == 2) {
        std::string inputFile, compressedFile, decompressedFile;
        std::cout << "Enter input file name: ";
        std::cin >> inputFile;
        std::cout << "Enter compressed output file name: ";
        std::cin >> compressedFile;
        std::cout << "Enter decompressed output file name: ";
        std::cin >> decompressedFile;

        // Read input file
        std::ifstream inFile(inputFile);
        if (!inFile.is_open()) {
            std::cout << "Error: Cannot open input file!" << std::endl;
            return 1;
        }
        std::string text((std::istreambuf_iterator<char>(inFile)),
                          std::istreambuf_iterator<char>());
        inFile.close();

        // Build frequency map and tree
        std::unordered_map<char, int> freqMap;
        buildFrequencyMap(text, freqMap);
        Node* root = buildHuffmanTree(freqMap);

        // Build codes
        std::unordered_map<char, std::string> codes;
        buildCodes(root, "", codes);

        // Compress
        std::string compressed = compress(text, codes);

        // Write compressed file
        std::ofstream outFile(compressedFile);
        outFile << compressed;
        outFile.close();

        // Show stats
        std::cout << "\nOriginal size:     " << text.size() << " characters" << std::endl;
        std::cout << "Compressed size:   " << compressed.size() << " bits" << std::endl;
        std::cout << "Compression ratio: " << (float)compressed.size() / (text.size() * 8) * 100 << "%" << std::endl;
        std::cout << "Compressed file saved to: " << compressedFile << std::endl;

        // Decompress using same tree
        std::string decompressed = decompress(compressed, root);

        // Write decompressed file
        std::ofstream decFile(decompressedFile);
        decFile << decompressed;
        decFile.close();

        std::cout << "Decompressed file saved to: " << decompressedFile << std::endl;

        // Verify
        if (text == decompressed) {
            std::cout << "\nVerification: SUCCESS ✅ Files match!" << std::endl;
        } else {
            std::cout << "\nVerification: FAILED ❌ Files don't match!" << std::endl;
        }

        deleteTree(root);
        std::cout << "Done!" << std::endl;

    } else {
        std::cout << "Invalid choice!" << std::endl;
    }

    return 0;
}