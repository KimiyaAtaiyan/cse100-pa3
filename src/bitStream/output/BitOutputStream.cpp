/**
 * TODO: file header
 *
 * Author:
 */
#include "BitOutputStream.hpp"

/* TODO */
void BitOutputStream::flush() {

	out<< buf;
	nbits = 0;

}

/* TODO */
void BitOutputStream::writeBit(int i) {

	if(nbits == byte_size){
		flush();
	}
	
	int loc = byte_size-nbits-1;
	buf = buf|(i << loc);
	nbits++;

}
