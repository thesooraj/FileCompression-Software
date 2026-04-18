#include "huffman.h"

int main() {
    std::cout << "====================================" << std::endl;
    std::cout << "   Huffman File Compression Tool    " << std::endl;
    std::cout << "====================================" << std::endl;

    int choice;
    std::cout << "\n1. Compress a file" << std::endl;
    std::cout << "2. Decompress a file" << std::endl;
    std::cout << "\nEnter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
        std::string inputFile, outputFile;
        std::cout << "Enter input file name: ";
        std::cin >> inputFile;
        std::cout << "Enter output file name: ";
        std::cin >> outputFile;

        std::cout << "\nCompressing..." << std::endl;
        compressFile(inputFile, outputFile);
        std::cout << "Done!" << std::endl;

    } else if (choice == 2) {
        std::string inputFile, outputFile;
        std::cout << "Enter compressed file name: ";
        std::cin >> inputFile;
        std::cout << "Enter output file name: ";
        std::cin >> outputFile;

        // Rebuild tree for decompression
        std::ifstream inFile(inputFile);
        std::string compressed((std::istreambuf_iterator<char>(inFile)),
                                std::istreambuf_iterator<char>());
        inFile.close();

        std::unordered_map<char, int> freqMap;
        std::unordered_map<char, std::string> codes;
        Node* root = buildHuffmanTree(freqMap);
        buildCodes(root, "", codes);

        std::cout << "\nDecompressing..." << std::endl;
        decompressFile(inputFile, outputFile, root);
        std::cout << "Done!" << std::endl;

        deleteTree(root);

    } else {
        std::cout << "Invalid choice!" << std::endl;
    }

    return 0;
}