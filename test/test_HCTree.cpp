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
    HCTree tree3;
    HCTree tree4;

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
        
	vector<unsigned int> freqs3(256);
        freqs3['a'] = 2;
        freqs3['b'] = 4;
        freqs3['j'] = 2;
        freqs3['c'] = 4;
        tree3.build(freqs3);

	vector<unsigned int> freqs4(256);
	freqs4['a']=  10;
	tree4.build(freqs4);
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

TEST_F(SimpleHCTreeFixture, TEST_DECODE_TREE2){

	istringstream is("001");
	ASSERT_EQ(tree2.decode(is), 'h');
}

TEST_F( SimpleHCTreeFixture, TEST_ENCODE_TREE2){
	ostringstream os;
	tree2.encode('a', os);
	ASSERT_EQ(os.str(), "11");
}

TEST_F(SimpleHCTreeFixture, TEST_ENCODE_TREE2_2){
	ostringstream os;
	tree2.encode('c', os);
	ASSERT_EQ(os.str(), "10");
}

TEST_F( SimpleHCTreeFixture, TEST_ENCODE_TREE3){
	ostringstream os;
	tree3.encode('a', os);
	ASSERT_EQ(os.str(), "00");

	ostringstream os2;
	tree3.encode('c', os2);
	ASSERT_EQ(os2.str(), "11");
	
	ostringstream os3;
	tree3.encode('b', os3);
	ASSERT_EQ(os3.str(), "10");

	ostringstream os4;
	tree3.encode('j', os4);
	ASSERT_EQ(os4.str(), "01");
}

TEST_F( SimpleHCTreeFixture, TEST_DELETE){
	HCTree* tree4;
	tree4 = new HCTree();
	delete tree4;
}

TEST_F(SimpleHCTreeFixture, TEST_SINGLE_NODE_DECODE){

	ostringstream os;
	tree4.encode('a', os);
	ASSERT_EQ(os.str(), "0");
	istringstream is("0");
	//ASSERT_EQ(tree4.decode(is), 'a');
}
