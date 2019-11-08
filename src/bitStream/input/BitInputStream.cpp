/**
 * Author: Kimiya Ataiyan, Meghana Sridhar
 * PID: A15753878, A13299951
 * Date: 11/6/2019
 * Filename: BitInputStream.cpp
 * Source of help: tutors
 */
#include "BitInputStream.hpp"

/* TODO */
void BitInputStream::fill() {

	//read byte by byte from input stream
	
	int val = in.get();
	
	if(in.eof()){
		
		return;
	}

	buf =(char)val;
	
	nbits = byte_size2;

}

/* TODO */
unsigned int BitInputStream::readBit() { 

	unsigned int bitRead;
	//fill the buffer with 1 byte from file
	if(nbits == 0){	
		fill();
	}

	bitRead = (unsigned int)((buf>>(nbits-1))&1);
	nbits--;


	return bitRead;
}

