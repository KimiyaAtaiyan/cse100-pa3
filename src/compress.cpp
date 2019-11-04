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
/*	vector<unsigned int> frequencies(size_vec);
	unsigned char symbol;
	HCTree* tree;
	ostream out;

	ifstream in;
	in.open(inFileName);

	while(1){
	
	      //read symbols from file on at a time
	      symbol = (unsigned char)in.get();

	      if(in.eof()){
	        break;
	      }

	      if( frequencies[(int)symbol] == 0){

	    	  frequencies[(int)symbol] = 1;
	      }
	      else{

		   frequencies[(int)symbol] = frequencies[(int)symbol]+1;
		}
	}

	//open compressed file
	out.open(outFileName);
	
	for (int i = 0; i < frequencies.size(); i++){
	  out.put(frequencies[i]);
	  out.put('\n');
	}

	//build the tree
	tree->build(frequencies);
	
	//encode on tree
	for (int i = 0; i < frequencies.size(); i++){
	  if (frequencies[i] != 0){
	    tree->encode((byte) i, out);
	  }
	}

	in.close(inFileName);*/

}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the compress */
int main(int argc, char* argv[]) { 
/*	if (argc != 2){
		return -1;
	}
	
	string inFile = argv[0];
	string outFile = argv[1];
	
	if (!isValidFile(inFile)){
	  return -1;
	}
	if (isEmptyFile(inFile)){
	  return -1;
	}

	pseudoCompression(inFile, outFile);
	//trueCompression(inFile, outFile);*/
	
	return 0; 

}
