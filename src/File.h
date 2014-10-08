#ifndef FILE_H
#define FILE_H


#include <iostream>
#include <stdio.h>

#include "Defines.h"


class File {

public:
	File(const char *file, const char *arg);
	~File(void);
	void close();

	FILE *pointer;
	FILE_SIZE size;

};

#endif // FILE_H
