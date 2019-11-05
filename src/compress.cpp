/**
 * File Name: compress.cpp
 * Author: Kimiya Ataiyan, Meghana Sridhar
 * PIDs: A15753878, A13299951
 * Date: 11/4/2019
 */
#include <fstream>
#include <iostream>
#include <vector>
#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

/* TODO: add pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void pseudoCompression(string inFileName, string outFileName) {


	vector<unsigned int> frequencies(size_vec,0);
	unsigned char symbol;
	int val;
	HCTree tree;

	ofstream outFile;
	ifstream in;

	//open files
	in.open(inFileName);
	outFile.open(outFileName , ios::binary);

	while(1){
	
	      //read symbols from file on at a time
	      //symbol = (unsigned char)in.get();
	      val = in.get();
		
	      if(in.eof()){
		      break;
	      }

	      symbol = (unsigned char)val;
	      frequencies[symbol]++;
	      
	}

	


	for (int i = 0; i < frequencies.size(); i++){
		outFile << frequencies[i] << endl;

	}

	//build the tree
	tree.build(frequencies);

		
	//encode on tree
	for (int i = 0; i < frequencies.size(); i++){
	  if (frequencies[i] != 0){
	    tree.encode((byte) i, outFile);
	  }
	}

	in.close();
	outFile.close();

}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the compress */
int main(int argc, char* argv[]) { 

	string inFile = argv[1];
	string outFile = argv[2];
	
	if (!FileUtils::isValidFile(inFile)){
	  return -1;
	}
	if (FileUtils::isEmptyFile(inFile)){
	  return -1;
	}
	pseudoCompression(inFile, outFile);

	//trueCompression(inFile, outFile);
	
	return 0; 

}
