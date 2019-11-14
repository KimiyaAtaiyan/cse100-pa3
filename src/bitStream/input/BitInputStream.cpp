/**
 * Author: Kimiya Ataiyan, Meghana Sridhar
 * PID: A15753878, A13299951
 * Date: 11/6/2019
 * Filename: BitInputStream.cpp
 * Source of help: tutors
 */
#include "BitInputStream.hpp"

/* Function Name: fill
 * Function Prototype: void fill()
 * Description: fills the buffer with a byte from reading from the input File
 * Return: none
 */
void BitInputStream::fill() {
    // read byte by byte from input stream

    int val = in.get();

    if (in.eof()) {
        return;
    }

    buf = (char)val;

    nbits = byte_size2;
}

/* Function name: readBit
 * Function prototype: unsigned int readBit()
 * Description: reads from the buffer bit by bit, and fills it once each bit
 * 		from buffer has been read.
 * Return: 0 or 1, depending on the bit read at that index
 */
unsigned int BitInputStream::readBit() {
    unsigned int bitRead;

    // fill the buffer with 1 byte from file
    if (nbits == 0) {
        fill();
    }

    bitRead = (unsigned int)((buf >> (nbits - 1)) & 1);
    nbits--;

    return bitRead;
}
