/**
 * File Name: uncompress.cpp
 * Author: Kimiya Ataiyan, Meghana Sridhar
 * PID: A15753878, A13299951
 * Date: 11/4/19
 * Description: Performs decompression on a file and writes the result to an
 * 		output file
 * Source of help: Tutors
 */
#include <fstream>
#include <iostream>
#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"
#include "cxxopts.hpp"

/*
 * Function: pseudoDecompression()
 * Function Prototype: void pseudoDecompression(string inFileName,
 * 						string outFileName)
 * Description: Pseudo decompression with ascii encoding and naive
 * 		header (checkpoint)
 * Parameters: string inFileName - the name of input file
 * 	       string outFileName - the name of output file
 * Returns: void
 */
void pseudoDecompression(string inFileName, string outFileName) {
    // Checks if input file is empty
    if (FileUtils::isEmptyFile(inFileName)) {
        ofstream outFile;
        outFile.open(outFileName);
        outFile.close();
        return;
    }

    // Declares local variables
    vector<unsigned int> frequencies(size_vec, 0);
    int count = 0;
    string val;
    HCTree tree;

    // Declares input stream and opens file as binary
    ifstream in;
    in.open(inFileName, ios::binary);

    // Loops till the 256th line
    while (1) {
        if (count == size_vec) {
            break;
        }
        // Gets the line in header
        getline(in, val);

        // Populates frequencies
        if (count < size_vec) {
            frequencies[count] = stoi(val);
        }
        count++;
    }

    // Builds Huffman Coding Tree based on header of file
    tree.build(frequencies);

    // Open output file and write decoded chars to it
    ofstream outFile;
    outFile.open(outFileName, ios::binary);

    // Loops till eof
    while (1) {
        // Writes decoded char into output file
        outFile << tree.decode(in);

        // Checks if next character is eof
        if (in.peek() == -1) {
            break;
        }
    }

    // Closes files
    in.close();
    outFile.close();
}

/*
 * Function: trueDecompression()
 * Function Prototype: void trueDecompression(string inFileName,
 * 						string outFileName)
 * Description: True decompression with bitwise i/o and small header
 * Parameters: string inFileName - the name of input file
 * 	       string outFileName - the name of output file
 * Returns: void
 */
void trueDecompression(string inFileName, string outFileName) {
    // Checks if input file is empty
    if (FileUtils::isEmptyFile(inFileName)) {
        ofstream outFile;
        outFile.open(outFileName);
        outFile.close();
        return;
    }

    // Declares local variables
    vector<unsigned int> frequencies(size_vec, 0);
    int count = 0;
    string val;
    HCTree tree;

    // Declares input stream and opens file as binary
    ifstream in;
    in.open(inFileName, ios::binary);
    BitInputStream bis(in);

    // Loops till the 256th line
    while (1) {
        if (count == size_vec) {
            break;
        }
        // Gets the line in header
        getline(in, val);

        // Populates frequencies
        if (count < size_vec) {
            frequencies[count] = stoi(val);
        }
        count++;
    }

    // Builds Huffman Coding Tree based on header of file
    tree.build(frequencies);

    // Open output file and write decoded chars to it
    ofstream outFile;
    outFile.open(outFileName, ios::binary);

    int numSymbsRead = 0;
    // Loops till eof
    while (numSymbsRead < numSymbols) {
        // Writes decoded char into output file
        outFile << tree.decode(bis);
        numSymbsRead++;
    }

    // Closes files
    in.close();
    outFile.close();
}

/*
 * Function: main()
 * Function Prototype: int main(int argc, char* argv[])
 * Description: Main program that runs the uncompress
 * Parameters: int argc - the number of arguments passed in
 * 	       char* argv[] - contains the arguments
 * Returns: int to indicate the success of the program
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
        pseudoDecompression(inFile, outFile);
    } else {
        trueDecompression(inFile, outFile);
    }

    return 0;
}
