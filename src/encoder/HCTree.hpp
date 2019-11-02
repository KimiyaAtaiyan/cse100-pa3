/**
 * TODO: file header
 *
 * Author:
 */
#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <fstream>
#include <queue>
#include <vector>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCNode.hpp"

using namespace std;

const int size_vec = 256;

/** TODO: class header */
class HCTree {
  private:
    HCNode* root;            // the root of HCTree
    vector<HCNode*> leaves;  // a vector storing pointers to all leaf HCNodes

    typedef priority_queue< HCNode*, vector<HCNode*>, HCNodePtrComp> pq;


    /*Helper Function*/
    void buildHelper(pq& myQueue);

    /*Helper Function encoding*/
//    bool encodeHelper(HCNode* curr, string& binString, byte symbol);

  public:
    /* TODO: add function header and implement */
    HCTree() {
    	root = nullptr;
   	leaves = vector<HCNode*>(size_vec); 
    }

    /* TODO: add function header */
    ~HCTree();

    /* TODO: add function header */
    void build(const vector<unsigned int>& freqs);

    /* TODO: add function header */
    void encode(byte symbol, BitOutputStream& out) const;

    /* TODO: add function header */
    void encode(byte symbol, ostream& out) const;

    /* TODO: add function header */
    byte decode(BitInputStream& in) const;

    /* TODO: add function header */
    byte decode(istream& in) const;
};

#endif  // HCTREE_HPP
