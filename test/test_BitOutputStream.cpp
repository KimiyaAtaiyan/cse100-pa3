#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "BitOutputStream.hpp"

using namespace std;
using namespace testing;

TEST(BitOutputStreamTests, SIMPLE_TEST) {
    stringstream ss;
    BitOutputStream bos(ss);
    bos.writeBit(1);
    bos.flush();

    string bitsStr = "10000000";
    unsigned int asciiVal = stoi(bitsStr, nullptr, 2);
    ASSERT_EQ(ss.get(), asciiVal);
}

TEST(BitOutputStreamTests, TEST_WRITE_FLUSH) {
    stringstream ss;
    BitOutputStream bos(ss);
    bos.writeBit(0);
    bos.flush();

    string bitStr = "00000000";
    unsigned int asciiVal = stoi(bitStr, nullptr, 2);
    ASSERT_EQ(ss.get(), asciiVal);
}
