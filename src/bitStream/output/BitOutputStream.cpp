/**
 * Author: Kimiya Ataiyan, Meghana Sridhar
 * PID: A15753878, A13299951
 * Date: 11/14/19
 * Source of help: tutors in lab
 */
#include "BitOutputStream.hpp"

/* Function name: flush
 * Function Prototype: void flush()
 * Description: flushes the contents of buffer(1 byte) and writes it to the
 * outFile Return: none
 */
void BitOutputStream::flush() {
    out.put(buf);
    out.flush();
    buf = 0;
    nbits = 0;
}

/* Function name: writeBit
 * Function Prototype: void writeBit(int i)
 * Description: sets the bits in buffer bit by bit until
 * 		8 bits have been written. Calls flush to reset and empty
 * 		buffer
 * Parameters: int i, integer converted to binary to write to Buffer
 * Return: none
 */
void BitOutputStream::writeBit(int i) {
    int loc = byte_size - nbits - 1;
    i = i & 1;
    buf = buf | (i << loc);
    nbits++;

    if (nbits == byte_size) {
        flush();
    }
}
