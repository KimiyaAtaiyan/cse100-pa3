/**
 * Author: Kimiya Ataiyan, Meghana Sridhar
 * PID: A157573878, A13299951
 * Date: 11/14/19
 * Source of help: Tutors in Lab
 */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;
int byte_size = 8;

/* Class Name: BitOutputStream
 * Description: contains functions flush and writeBit, which have implementation
 * 		to fill the buffer bit by bit
 */
class BitOutputStream {
  private:
    char buf;      // one byte buffer of bits
    int nbits;     // number of bits have been writen to buf
    ostream& out;  // reference to the output stream to use

  public:
    /* Constructor of the class BitOutputStream */
    explicit BitOutputStream(ostream& os) : out(os) {
        nbits = 0;
        buf = 0;
    };

    /* flushes the contents of the buffer and writes it to File*/
    void flush();

    /* Writes the bits in the buffer until buffer is full*/
    void writeBit(int i);
};

#endif
