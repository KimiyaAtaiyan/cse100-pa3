/**
 * TODO: file header
 *
 * Author:
 */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;
int byte_size = 8;

/** TODO: class header */
class BitOutputStream {
  private:
    char buf;      // one byte buffer of bits
    int nbits;     // number of bits have been writen to buf
    ostream& out;  // reference to the output stream to use

  public:
    /* TODO: add function header and implement */
    explicit BitOutputStream(ostream& os) : out(os) {
        nbits = 0;
        buf = 0;
    };

    /* TODO: add function header */
    void flush();

    /* TODO: add function header */
    void writeBit(int i);
};

#endif
