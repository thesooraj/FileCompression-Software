# FileCompression-Software
# Huffman File Compression Tool

A file compression and decompression tool built in C++ using the Huffman Coding algorithm.

## What is Huffman Coding?
Huffman Coding is a lossless data compression algorithm. It assigns shorter
binary codes to characters that appear more frequently and longer codes to
characters that appear less frequently. This reduces the overall size of the file.

## How it works
1. Read the input file and count frequency of each character
2. Build a Huffman tree based on character frequencies
3. Generate binary codes for each character
4. Replace each character with its binary code
5. Save the compressed output

## Project Structure

| File | Purpose |
|---|---|
| main.cpp | Main program with user interface |
| huffman.h | Header file with node structure and function declarations |
| huffman.cpp | Implementation of all compression and decompression functions |

## How to Compile
Open terminal in this folder and type:

    g++ -o FileCompression main.cpp huffman.cpp

## How to Run

    ./FileCompression

## Menu Options
- Option 1: Compress a file only
- Option 2: Compress and decompress a file with verification

## Example Output
Original size:     50 characters
Compressed size:   198 bits
Compression ratio: 49.5%
Compressed file saved to: compressed.txt
Decompressed file saved to: decompressed.txt
Verification: SUCCESS  Files match!

## Features
- Compresses any text file using Huffman Coding
- Decompresses back to original file
- Shows compression ratio
- Verifies decompressed file matches original
- Memory efficient with proper tree cleanup

## Algorithm Steps
1. Build frequency map from input text
2. Create a min heap priority queue with all characters
3. Build Huffman tree by combining two lowest frequency nodes
4. Traverse tree to generate binary codes
5. Encode text using generated codes
6. Decode using same tree structure