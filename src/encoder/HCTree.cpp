/**
 * File Name: HCTree.cpp
 * Author: Kimiya Ataiyan, Meghana Sridhar
 * PIDs: A15753878, A1329951
 * Description: Contains the method functionality to build, encode and decode
 *    		a tree
 * Sources of Help: Tutors
 */
#include "HCTree.hpp"
#include <bits/stdc++.h>
#include <stdlib.h>
#include <ostream>
#include <string>
#include <vector>

/**
 * Function Name: ~HCTree() (destructor)
 * Function Prototype: ~HCTree()
 * Description: Calls the deleteAll to delete the tree
 * Parameters: None
 * Returns: None
 */
HCTree::~HCTree() { deleteAll(root); }

/**
 * Function Name: build()
 * Function Prototype: void build(const vector<unsigned int>& freqs)
 * Description: Builds the tree node by node
 * Parameters: const vector<unsigned int>& freqs - the frequency array
 *         containing ASCII indices with their respective frequencies
 * Returns: None
 */
void HCTree::build(const vector<unsigned int>& freqs) {
    // Priority queue
    pq myQueue;

    // Use myQueue to sort frequency in ascending order
    for (int i = 0; i < freqs.size(); i++) {
        if (freqs[i] != 0) {
            // Initializes new node, pushes node onto Queue and populates leaves
            HCNode* newNode =
                new HCNode(freqs[i], (byte)i, nullptr, nullptr, nullptr);
            numSymbols = numSymbols + freqs[i];
            myQueue.push(newNode);
            leaves[i] = newNode;
        }
    }
    // call helper function to build tree
    buildHelper(myQueue);
}

/**
 * Function Name: buildHelper()
 * Function Prototype: void buildHelper(pq& myQueue)
 * Description: Recursively connects the nodes to build the tree
 * Parameters: pq& myQueue - contains the nodes of the tree
 * Returns: None
 */
void HCTree::buildHelper(pq& myQueue) {
    // Base case
    if (myQueue.size() <= 1) {
        // Initializes root
        root = myQueue.top();
        myQueue.pop();
        return;
    }

    // Initializes left child
    HCNode* child0 = myQueue.top();
    myQueue.pop();
    // Initializes right child
    HCNode* child1 = myQueue.top();
    myQueue.pop();

    // Creates parentNode
    HCNode* parentNode = new HCNode(child0->count + child1->count,
                                    child1->symbol, child0, child1, nullptr);
    // Connects children to parent
    child0->p = parentNode;
    child1->p = parentNode;

    // Push parentNode onto Queue
    myQueue.push(parentNode);
    // Recursive call to helper
    buildHelper(myQueue);
    return;
}

/*
 * Function name: encode
 * Function Prototype: void encode(byte symbol, BitOutputStream&out) const
 * Description: write the encoding bits of given symbol to BitOutputStream
 * Return: none
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    HCNode* curr = leaves[(int)symbol];
    string binString = "";

    if (curr == nullptr) {
        return;
    }

    // Return 0 if only root in tree
    if (curr == root) {
        out.writeBit(0);
        return;
    }

    // Loops till curr is root
    while (curr != root) {
        // Check if current is left child
        if (curr == curr->p->c0) {
            // Append 0 going left
            binString.append("0");
            curr = curr->p;
        } else if ((curr == curr->p->c1)) {
            // Append 1 going right
            binString.append("1");
            curr = curr->p;
        }
    }

    // Reverse string
    reverse(binString.begin(), binString.end());
    nbitsWritten = nbitsWritten + binString.length();

    // Loops through binString
    for (int i = 0; i < binString.length(); i++) {
        // Outputs the bits of the binary string
        out.writeBit((int)binString[i]);
    }
    return;
}

/**
 * Function Name: encode
 * Function Prototype: void encode(byte symbol, ostream& out) const
 * Description: Encodes a byte by traversing the tree and assigning a unique
 *    bit code
 * Parameters: byte symbol - the character to be encoded
 *         ostream& out - file to write the encoded symbol to
 * Returns: None
 */
void HCTree::encode(byte symbol, ostream& out) const {
    // Use leaves vector to recurse up the tree
    HCNode* curr = leaves[(int)symbol];
    string binString = "";

    // Return if no leaves
    if (curr == nullptr) {
        return;
    }

    // Return 0 if only root in tree
    if (curr == root) {
        out.put('0');
        return;
    }

    // Loops till curr is root
    while (curr != root) {
        // Check if current is left child
        if (curr == curr->p->c0) {
            // Append 0 going left
            binString.append("0");
            curr = curr->p;
        } else if ((curr == curr->p->c1)) {
            // Append 1 going right
            binString.append("1");
            curr = curr->p;
        }
    }

    // Reverse string
    reverse(binString.begin(), binString.end());

    // Loops through binString
    for (int i = 0; i < binString.length(); i++) {
        // Outputs the bits of the binary string
        out.put(binString[i]);
    }
    return;
}

/*
 * Function name: decode
 * Function Prototype: byte decode(BitInputStream& in) const
 * Description: Decode the sequence from the given BitInputStream to return
 * 		the coded symbol
 * Return: byte representing the coded symbol
 */
byte HCTree::decode(BitInputStream& in) const {
    // Checks if root is null
    if (root == nullptr) {
        return '\0';
    }

    // Initializes the local variables
    HCNode* curr = root;
    byte retSymbol = '\0';
    unsigned int character = in.readBit();

    // Loops till curr is null
    while (curr != nullptr) {
        // Checks if eof
        if (character != -1) {
            // Sets return Symbol to current symbol
            retSymbol = curr->symbol;
            // Checks if character is 0
            if (character == 0) {
                curr = curr->c0;
            } else {
                curr = curr->c1;
            }

            // Checks if curr is a leaf node
            if (find(leaves.begin(), leaves.end(), curr) == leaves.end()) {
                // Gets the next character from input file
                character = in.readBit();
            }
        } else {
            break;
        }
    }
    return retSymbol;
}

/**
 * Function Name: decode()
 * Function Prototype: byte decode(istream& in) const
 * Description: Decodes one byte at a time given an input file
 * Parameters: istream& in - input file
 * Returns: byte that has been decoded
 */
byte HCTree::decode(istream& in) const {
    // Checks if root is null
    if (root == nullptr) {
        return '\0';
    }

    // Initializes the local variables
    HCNode* curr = root;
    byte retSymbol = '\0';
    char character = (char)in.get();

    // Loops till curr is null
    while (curr != nullptr) {
        // Checks if eof
        if ((int)character != -1) {
            // Sets return Symbol to current symbol
            retSymbol = curr->symbol;
            // Checks if character is 0
            if (character == '0') {
                curr = curr->c0;
            } else {
                curr = curr->c1;
            }

            // Checks if curr is a leaf node
            if (find(leaves.begin(), leaves.end(), curr) == leaves.end()) {
                // Gets the next character from input file
                character = (char)in.get();
            }
        } else {
            break;
        }
    }
    return retSymbol;
}

/*
 * Function name: deleteAll()
 * Function Prototype: void deleteAll(HCNode* curr)
 * Description: Deletes all memory allocated on heap
 * Parameters: Node* curr - current node to begin deleting from
 * Return: none
 */
void HCTree::deleteAll(HCNode* curr) {
    // Checks if curr is null
    if (curr == nullptr) {
        return;
    }
    // Checks if child is null
    if (curr != nullptr) {
        // Deletes all left children
        deleteAll(curr->c0);
        // Deletes all right children
        deleteAll(curr->c1);
        // Deletes node
        delete curr;
    }
}
