/**
 * File Name: HCTree.hpp
 * Author: Kimiya Ataiyan, Meghana Sridhar
 * PID: A15753878, A1329951
 * Description: Contains definitions of HCTree class and its methods
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
int nbitsWritten;
int numSymbols;
int leafBitsWritten;

/**
 * Class Name: HCTree
 * Description: Defines methods and private variables for an HCTree
 **/
class HCTree {
  private:
    HCNode* root;            // the root of HCTree
    vector<HCNode*> leaves;  // a vector storing pointers to all leaf HCNodes

    typedef priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

    /*Helper Function for build*/
    void buildHelper(pq& myQueue);

  public:
    /* Constructor that defines root node and leaves vector*/
    HCTree() {
        root = nullptr;
        leaves = vector<HCNode*>(size_vec);
        numSymbols = 0;
        nbitsWritten = 0;
	leafBitsWritten = 0;
    }

    /* Desctructor that calls the deleteAll method*/
    ~HCTree();

    /* Builds the HCTree by linking HCNodes*/
    void build(const vector<unsigned int>& freqs);

    /* Writes the encoded leaf nodes to the BitOutputStream */
    void writeLeafNodes(BitOutputStream& out);

    /* Writes the encoded tree to the BitOutputStream*/
    void encodedTree(BitOutputStream& out);

    /* Encodes a byte by traversing through the HCTree using BitOutputStream*/
    void encode(byte symbol, BitOutputStream& out) const;

    /* Encodes a byte by traversing through the HCTree using ostream*/
    void encode(byte symbol, ostream& out) const;

    /* Decodes a byte by traversing through the HCTree using BitInputStream */
    byte decode(BitInputStream& in) const;

    /* Decodes a byte by traversing through the HCTree using istream*/
    byte decode(istream& in) const;

    /* Deletes all the nodes in the tree*/
    void deleteAll(HCNode* curr);
};

#endif  // HCTREE_HPP
