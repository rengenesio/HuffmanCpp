#ifndef NODEARRAY_H
#define NODEARRAY_H

#include <iostream>
#include "Node.h"

class NodeArray {

public:
	NodeArray(SIZE size);
	~NodeArray(void);
	void insertSorted(Node *n);
	void removeLastTwoNodes(void);
	void printArray(void);

	Node **node;
	SIZE size;

};

#endif // NODEARRAY_H
