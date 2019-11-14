/**
 * Author: Kimiya Ataiyan, Megahna Sridhar
 * PID: A15753878, A13299951
 *
 * Date: 11/14/19
 * FileName: BitInputStream.hpp
 * Source of help:tutors in Lab
 */
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;
int byte_size2 = 8;

/*
 * Class Name: BitInputStream
 * Description: contains two functions fill, and readBit, which fill
 *   		the buffer by reading bit by bit.
 */
class BitInputStream {
  private:
    char buf;     // one byte buffer of bits
    int nbits;    // number of bits have been writen to buf
    istream& in;  // reference to the input stream to use

  public:
    /*Constructor of the BitInputStream class*/
    explicit BitInputStream(istream& is) : in(is) {
        nbits = 0;
        buf = '0';
    };

    /* Fills the buffer*/
    void fill();

    /* Reads from file bit by bit*/
    unsigned int readBit();
};

#endif
