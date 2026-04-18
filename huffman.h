#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>

// Node structure for Huffman tree
struct Node {
    unsigned char character;
    int frequency;
    Node* left;
    Node* right;

    Node(unsigned char c, int freq) {
        character = c;
        frequency = freq;
        left = nullptr;
        right = nullptr;
    }
};

// Compare nodes for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

// Function declarations
void buildFrequencyMap(const std::vector<unsigned char>& data, std::unordered_map<unsigned char, int>& freqMap);
Node* buildHuffmanTree(std::unordered_map<unsigned char, int>& freqMap);
void buildCodes(Node* root, std::string code, std::unordered_map<unsigned char, std::string>& codes);
std::string compress(const std::vector<unsigned char>& data, std::unordered_map<unsigned char, std::string>& codes);
std::vector<unsigned char> decompress(const std::string& compressed, Node* root, int originalSize);
void deleteTree(Node* root);

#endif