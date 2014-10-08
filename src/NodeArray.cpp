#include "NodeArray.h"


NodeArray::NodeArray(SIZE size) {
	this->node = new Node *[size];
	this->size = 0;
}

NodeArray::~NodeArray(void) {
	for(SIZE i = 0 ; i < this->size ; i++)
		delete node[i];
	delete node;
}

void NodeArray::insertSorted(Node *n) {
	SIZE i;
	for(i = 0 ; i < this->size && this->node[i]->frequency > n->frequency ; i++);
	SIZE j;
	for(j = this->size ; j > i ; j--)
		this->node[j] = this->node[j-1];

	this->size++;
	this->node[j] = &(*n);
}

void NodeArray::removeLastTwoNodes(void) {
	this->size -= 2;
}

void NodeArray::printArray() {
	std::cerr << "NODE ARRAY: symbol(frequency)    left: [node]    right: [node]" << std::endl;
	for(POWER_SIZE i = 0 ; i < this->size ; i++) {
		std::cerr << (int) i << ": " << (int) this->node[i]->symbol << "(" << (int) this->node[i]->frequency << ") left: [";
		if(this->node[i]->left)
			std::cout << (int) this->node[i]->left->symbol << "(" << (int) this->node[i]->left->frequency << ")]  right: [";
		else
			std::cout << "N]  right: [";
		if(this->node[i]->right)
			std::cout << (int) this->node[i]->right->symbol << "(" << (int) this->node[i]->right->frequency << ")]" << std::endl;
		else
			std::cout << "N]" << std::endl;
	}
}
