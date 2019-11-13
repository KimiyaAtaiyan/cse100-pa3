/**
 * TODO: file header
 *
 * Author:
 */
#include "BitOutputStream.hpp"

/* TODO */
void BitOutputStream::flush() {
    out.put(buf);
    out.flush();
    buf = 0;
    nbits = 0;
}

/* TODO */
void BitOutputStream::writeBit(int i) {
    int loc = byte_size - nbits - 1;
    i = i & 1;
    buf = buf | (i << loc);
    nbits++;

    if (nbits == byte_size) {
        flush();
    }
}
