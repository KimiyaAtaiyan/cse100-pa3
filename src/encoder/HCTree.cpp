/**
 * Aut
 *
 * Author:
 */
#include "HCTree.hpp"

HCTree::~HCTree() {
	root = nullptr;
}

void HCTree::build(const vector<unsigned int>& freqs) {	

	pq myQueue;

	//use priority_queue to sort frequency in ascending order
	for(int i =0 ;i < freqs.size(); i++){

		if(freqs[i] != 0){

			myQueue.push(new HCNode(freqs[i], (byte)i, nullptr, nullptr, nullptr));
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


	HCNode* leftNode = myQueue.top();
	myQueue.pop();
	HCNode * rightNode = myQueue.top();
	myQueue.pop();

	HCNode* parentNode = new HCNode( leftNode->count + rightNode->count, rightNode->symbol, leftNode, rightNode, nullptr);
	leftNode->p = parentNode;
	rightNode->p = parentNode;

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

	HCNode* curr = root;
	string binString="";
	bool symbolFound = encodeHelper(curr, binString, symbol);

	//write to outstream if symbol found 
	if(symbolFound){

		out.write(binString, binString.length());
	}

	return;
}

bool HCTree::encodeHelper( HCNode* curr, string& binString, byte symbol){

	if(curr == nullptr){
		return false;
	}

	if(symbol < curr->symbol){

		//append 0 going left
		binString.append("0");
		encodeHelper(curr->c0, binString, symbol);
	}
	else if( symbol > curr->symbol){

		binString.append("1");
		encodeHelper(curr->c1, binString, symbol);
	}
	else{
		if(curr->symbol == symbol){

			return true;
		}
		return false;

	}

}
/* TODO */
byte HCTree::decode(BitInputStream& in) const { return ' '; }

/* TODO */
byte HCTree::decode(istream& in) const { return ' '; }
