/**
 * File Name: HCTree.cpp
 * Author:
 * PIDs: 
 * Description: 
 * Sources of Help: 
 */
#include "HCTree.hpp"
#include <ostream>
#include <string>
//#include <vector>
#include <bits/stdc++.h>


HCTree::~HCTree() {
  
  deleteAll(root);

}

void HCTree::build(const vector<unsigned int>& freqs) {	

	pq myQueue;

	//use priority_queue to sort frequency in ascending order
	for(int i =0 ;i < freqs.size(); i++){

		if(freqs[i] != 0){
			
			HCNode* newNode = new HCNode(freqs[i], (byte)i, nullptr,nullptr,nullptr);
			myQueue.push(newNode);
			leaves[i] = newNode;
		}


	}

	//call helper function to build tree
	buildHelper(myQueue);	
}

void HCTree::buildHelper(pq& myQueue){

	//Base case
	if(myQueue.size() <= 1){
		root = myQueue.top();
		myQueue.pop();
		return;
	}


	HCNode* child0 = myQueue.top();
	myQueue.pop();
	HCNode * child1 = myQueue.top();
	myQueue.pop();

	HCNode* parentNode = new HCNode( child0->count + child1->count, child1->symbol, child0, child1, nullptr);
	child0->p = parentNode;
	child1->p = parentNode;

	//push parent node back to queue
	myQueue.push(parentNode);


	//recursive call 
	buildHelper(myQueue);

	return;

}

/* TODO */
void HCTree::encode(byte symbol, BitOutputStream& out) const {}





/* TODO */
void HCTree::encode(byte symbol, ostream& out) const {

	//use leaves vector to recurse up the tree, reverse found string
	HCNode* curr = leaves[(int)symbol];
	string binString="";

	if(curr == nullptr){
		return;
	}

	while(curr != root){
		
		//check if current is left child
		if( curr == curr->p->c0){
			//append 0 going left
			binString.append("0");
			curr = curr->p;
		}
		else if(curr = curr->p->c1){
			//append 1 going right
			binString.append("1");
			curr = curr->p;
		}
	}

	//reverse string 
	reverse(binString.begin(), binString.end());

	for(int i = 0; i < binString.length(); i++){

		out.put(binString[i]);
	}

	return;
}



/* TODO */
byte HCTree::decode(BitInputStream& in) const { 
	return ' ';	
}

/* TODO */
byte HCTree::decode(istream& in) const { 
	
	if(root == nullptr){
		return NULL;
	}

	HCNode* curr = root;
	byte retSymbol = '\0';
	char character = (char)in.get();

	//read in the string from in 
	while(curr != nullptr && (int) character != -1){
		
		if((int)character != -1){
			if(character == '0'){
				curr = curr->c0;
				retSymbol = curr->symbol;
			}
			else{
				curr = curr->c1;
				retSymbol = curr->symbol;
			}
			character = (char)in.get();
		}
		else{
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
void HCTree::deleteAll(HCNode* curr){

  //Checks if curr is null
  if(curr == nullptr){
    return;
  }
  //Checks if child is null
  if (curr != nullptr){
    //Deletes all left children
    deleteAll(curr->c0);
    //Deletes all right children
    deleteAll(curr->c1);
    //Deletes node
    delete curr;
  } 
}

