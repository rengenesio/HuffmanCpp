#include "Node.h"

Node::Node(SYMBOL symbol, FREQUENCY frequency, Node *left, Node *right) {
	this->left = left;
	this->right = right;
	this->symbol = symbol;
	this->frequency = frequency;
	this->visited = 0;
}

Node::~Node(void) {
	delete left;
	delete right;
}

void Node::print(void) {
	std::cerr << (int) this->symbol << "(" << (int) this->frequency << ")" << (int) this->visited << "    L: ";
	if(left)
		std::cerr << (int) this->left->symbol << "(" << (int) this->left->frequency << ")" << (int) this->left->visited << "    R:";
	else
		std::cerr << "N  R: ";
	if(right)
		std::cerr << (int) this->right->symbol << "(" << (int) this->right->frequency << ")" << (int) this->right->visited << std::endl;
	else
		std::cerr << "N" << std::endl;

}

void Node::printTree(void) {
	if(this->left)
		left->printTree();
	std::cerr << (int) this->symbol << "(" << (int) this->frequency << ")" << std::endl;
	if(this->right)
		right->printTree();
}
