/**
 * File Name: compress.cpp
 * Author: Kimiya Ataiyan, Meghana Sridhar
 * PIDs: A15753878, A13299951
 * Date: 11/4/2019
 * Description: Performs compression on an input file
 * Sources of Help: Tutors
 */
#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"
#include "cxxopts.hpp"

/*
 * Function Name: pseudoCompression()
 * Functon Prototype: void pseudoCompression(string inFileName,
 *               string outFilename)
 * Description: Adds pseudo compression with ascii encoding and naive header
 * Parameters: string inFileName - the input file name
 *         string outFileName - the output file name
 * Returns: void
 */
void pseudoCompression(string inFileName, string outFileName) {
    // Checks if inputs file is empty
    if (FileUtils::isEmptyFile(inFileName)) {
        ofstream outFile;
        outFile.open(outFileName);
        outFile.close();
        return;
    }

    // Defines local variables
    vector<unsigned int> frequencies(size_vec, 0);
    unsigned char symbol;
    int val;
    HCTree tree;

    // Defines streams
    ofstream outFile;
    ifstream in;

    // Open files
    in.open(inFileName, ios::binary);
    outFile.open(outFileName);

    // Loop till eof
    while (1) {
        // Get char by char
        val = in.get();

        if (in.eof()) {
            break;
        }

        // Insert symbol and increment its frequency
        symbol = (unsigned char)val;
        frequencies[symbol]++;
    }

    // Loops through frequencies
    for (int i = 0; i < frequencies.size(); i++) {
        // Writes header
        outFile << frequencies[i] << endl;
    }

    // Builds the tree
    tree.build(frequencies);

    // Resets position to read input file
    in.clear();
    in.seekg(0, ios::beg);

    // Encode on tree
    while (1) {
        val = in.get();
        if (in.eof()) {
            break;
        }
        tree.encode((unsigned char)val, outFile);
    }

    // Close files
    in.close();
    outFile.close();
}

/*
 * Function Name: trueCompression()
 * Functon Prototype: void trueCompression(string inFileName,
 *               string outFilename)
 * Description: True compression with bitwise i/o and small header
 * Parameters: string inFileName - the input file name
 *         string outFileName - the output file name
 * Returns: void
 */
void trueCompression(string inFileName, string outFileName) {
    // Checks if inputs file is empty
    if (FileUtils::isEmptyFile(inFileName)) {
        ofstream outFile;
        outFile.open(outFileName);
        outFile.close();
        return;
    }

    // Defines local variables
    vector<unsigned int> frequencies(size_vec, 0);
    unsigned char symbol;
    int val;
    HCTree tree;

    // Defines streams
    ofstream outFile;
    ifstream inFile;

    // Open files
    outFile.open(outFileName);
    inFile.open(inFileName);

    BitOutputStream bos(outFile);

    // Loop till eof
    while (1) {
        // Get char by char
        val = inFile.get();

        if (inFile.eof()) {
            break;
        }

        // Insert symbol and increment its frequency
        symbol = (unsigned char)val;
        frequencies[symbol]++;
    }

    // Loops through frequencies
    for (int i = 0; i < frequencies.size(); i++) {
        // Writes header
        outFile << frequencies[i] << endl;
    }

    // Builds the tree
    tree.build(frequencies);

    // Resets position to read input file
    inFile.clear();
    inFile.seekg(0, ios::beg);

    // Encode on tree

    while (1) {
        val = inFile.get();
        if (inFile.eof()) {
            break;
        }
        tree.encode((unsigned char)val, bos);
    }

    int nbitsTotal = nbitsWritten;

    if (nbitsTotal % byte_size != 0) {
        bos.flush();
    }

    // Close files
    inFile.close();
    outFile.close();
}

/*
 * Function Name: main()
 * Functon Prototype: int main(int argc, char* argv[])
 * Description: Main program that runs the compress
 * Parameters: int argc - the number of arguments passed in
 *         char* argv[] - contains the arguments
 * Returns: int that indicates the success of program run
 */
int main(int argc, char* argv[]) {
    cxxopts::Options options("./compress",
                             "Compresses files using Huffman Encoding");
    options.positional_help("./path_to_input_file ./path_to_output_file");

    bool isAsciiOutput = false;
    string inFile;
    string outFile;

    options.allow_unrecognised_options().add_options()(
        "ascii", "Write output in ascii mode instead of bit stream",
        cxxopts::value<bool>(isAsciiOutput))("input", "",
                                             cxxopts::value<string>(inFile))(
        "output", "", cxxopts::value<string>(outFile))("h,help",
                                                       "Print help and exit");

    options.parse_positional({"input", "output"});
    auto userOptions = options.parse(argc, argv);

    if (userOptions.count("help") || !FileUtils::isValidFile(inFile) ||
        outFile.empty()) {
        cout << options.help({""}) << std::endl;
        exit(0);
    }

    if (isAsciiOutput) {
        pseudoCompression(inFile, outFile);
    } else {
        trueCompression(inFile, outFile);
    }

    return 0;
}
