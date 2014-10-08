#ifndef CODIFICATION_H
#define CODIFICATION_H


#include <iostream>
#include <string>

#include "Defines.h"


class Codification {

public:
	Codification(SYMBOL symbol = 0, std::string *code = NULL);
	~Codification(void);
	void print(void);

	SYMBOL symbol;
	std::string *code;
	SIZE size;

};

#endif // CODIFICATION_H
