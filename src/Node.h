#ifndef NODE_H
#define NODE_H


#include <iostream>
#include <stdlib.h>

#include "Defines.h"


class Node {

public:
	Node(SYMBOL symbol = 0, FREQUENCY frequency = 0, Node *left = NULL, Node *right = NULL);
	~Node(void);
	void print(void);
	void printTree(void);

	Node *left, *right;
	SYMBOL symbol;
	FREQUENCY frequency;
	bool visited;

};

#endif // NODE_H
