/**
 * Author: Kimiya Ataiyan, Meghana Sridhar
 * PID: A15753878, A13299951
 * Date: 11/4/19
 * Source of help: none
 */
#include <fstream>
#include <iostream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

/* TODO: Pseudo decompression with ascii encoding and naive header (checkpoint)
*/
void pseudoDecompression(string inFileName, string outFileName) {

	//build frequency vector from file 
	vector<unsigned int> frequencies(size_vec, 0);
	int count = 0;
	int val;
	HCTree tree;


	ifstream in;
	in.open(inFileName, ios::binary);

	while(1){

		val = in.get();

		if(count == 256){
			break;

		}

		if(count < size_vec){
			frequencies[count] = (unsigned int)val;
		}
		count++;
	}


	//build Huffman Coding Tree based on header of file
	tree.build(frequencies);

	//open decompressed file and write decoded chars to it 
	ofstream outFile;
	outFile.open(outFileName, ios::binary);

	while(1){

		if(in.eof()){
			break;
		}
		
		outFile.put(tree.decode(in));
	}


	in.close();
	outFile.close();

}

/* TODO: True decompression with bitwise i/o and small header (final) */
void trueDecompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the uncompress */
int main(int argc, char* argv[]) {



	string inFile = argv[1];
	string outFile = argv[2];

	if(!FileUtils::isValidFile(inFile)){
		return -1;
	}
	if(FileUtils::isEmptyFile(inFile)){
		return -1;
	}

	pseudoDecompression(inFile, outFile);
	//trueDecompression(inFile, outFile);


	return 0;
}
