/**
 * File Name: compress.cpp
 * Author: Kimiya Ataiyan, Meghana Sridhar
 * PIDs: A15753878, A13299951
 * Date: 11/4/2019
 * Description: Performs compression on an input file
 * Sources of Help: Tutors
 */
#include <fstream>
#include <iostream>
#include <vector>
#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

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
  //Defines local variables
  vector<unsigned int> frequencies(size_vec,0);
  unsigned char symbol;
  int val;
  HCTree tree;

  //Defines streams
  ofstream outFile;
  ifstream in;

  //Open files
  in.open(inFileName, ios::binary);
  outFile.open(outFileName);

  //Loop till eof
  while(1){

    //Get char by char
    val = in.get();

    if(in.eof()){
      break;
    }

    //Insert symbol and increment its frequency
    symbol = (unsigned char)val;
    frequencies[symbol]++;
  }
  
  //Loops through frequencies
  for (int i = 0; i < frequencies.size(); i++){
    //Writes header
    outFile << frequencies[i] << endl;

  }

  //Builds the tree
  tree.build(frequencies);
  
  //Resets position to read input file
  in.clear();
  in.seekg(0, ios::beg);

  //Encode on tree
  while(1){
    val = in.get();
    if (in.eof()){
      break;
    }
    tree.encode((unsigned char) val, outFile);
  }

  //Close files
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

  //Defines local variables
  vector<unsigned int> frequencies(size_vec,0);
  unsigned char symbol;
  int val;
  HCTree tree;

  //Defines streams
  ostream out;
  istream in;


  //Open files
	out.open();
	in.open();


  BitOutputStream bos(outFile);
  BitInputStream bis(inFile);


  //Loop till eof
  while(1){

    //Get char by char
    val = in.get();

    if(in.eof()){
      break;
    }

    //Insert symbol and increment its frequency
    symbol = (unsigned char)val;
    frequencies[symbol]++;
  }
  

  //Loops through frequencies
  for (int i = 0; i < frequencies.size(); i++){
    //Writes header
     out << frequencies[i] << endl;
  }

  //Builds the tree
  tree.build(frequencies);
  
  //Resets position to read input file
  in.clear();
  in.seekg(0, ios::beg);

  //Encode on tree

  while(1){
    val = in.get();
    if (in.eof()){
      break;
    }
    tree.encode((unsigned char) val, bos);
  }

  //Close files
  in.close();
  out.close();

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
  //Store the input and output file (names)
  string inFile = argv[1];
  string outFile = argv[2];

  //Checks if input file is valid
  if (!FileUtils::isValidFile(inFile)){
    return -1;
  }
  //Checks if inputs file is empty
  if (FileUtils::isEmptyFile(inFile)){
    return -1;
  }
  //Calls pseudoCompression
  pseudoCompression(inFile, outFile);

  //trueCompression(inFile, outFile);

  return 0; 
}
