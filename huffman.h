#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>

// This struct represents a single node in the Huffman tree
struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;

    // Constructor to create a new node
    Node(char c, int freq) {
        character = c;
        frequency = freq;
        left = nullptr;
        right = nullptr;
    }
};

// This is used to compare nodes in the priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

// Function declarations
void buildFrequencyMap(const std::string& text, std::unordered_map<char, int>& freqMap);
Node* buildHuffmanTree(std::unordered_map<char, int>& freqMap);
void buildCodes(Node* root, std::string code, std::unordered_map<char, std::string>& codes);
std::string compress(const std::string& text, std::unordered_map<char, std::string>& codes);
std::string decompress(const std::string& compressed, Node* root);
void compressFile(const std::string& inputFile, const std::string& outputFile);
void decompressFile(const std::string& inputFile, const std::string& outputFile, Node* root);
void deleteTree(Node* root);

#endif