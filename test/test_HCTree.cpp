#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "HCTree.hpp"

using namespace std;
using namespace testing;

class SimpleHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree;
    HCTree tree2;

  public:
    SimpleHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 2;
        freqs['b'] = 3;
        tree.build(freqs);



	vector<unsigned int> freqs2(256);
	freqs2['a'] = 6;
	freqs2['b'] = 4;
	freqs2['c'] = 4;
	freqs2['g'] = 1;
	freqs2['h'] = 2;
	tree2.build(freqs2);
    }
};

TEST_F(SimpleHCTreeFixture, TEST_ENCODE) {
    ostringstream os;
    tree.encode('a', os);
    ASSERT_EQ(os.str(), "0");
}

TEST_F(SimpleHCTreeFixture, TEST_DECODE) {
    istringstream is("1");
    ASSERT_EQ(tree.decode(is), 'b');
}


TEST_F( SimpleHCTreeFixture, TEST_ENCODE_TREE2){
	ostringstream os;
	tree.encode('a', os);
	ASSERT_EQ(os.str(), "0000");
}

TEST_F(SimpleHCTreeFixture, TEST_ENCODE_TREE2_2){
	ostringstream os;
	tree.encode('c', os);
	ASSERT_EQ(os.str(), "001");
}

