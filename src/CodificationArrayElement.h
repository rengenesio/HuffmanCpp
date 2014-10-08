#ifndef CODIFICATIONARRAYELEMENT_H
#define CODIFICATIONARRAYELEMENT_H


#include "Defines.h"


class CodificationArrayElement {

public:
	CodificationArrayElement(void);
	CodificationArrayElement(SYMBOL symbol);
	~CodificationArrayElement(void);

	SYMBOL symbol;
	bool used;

};

#endif // CODIFICATIONARRAYELEMENT_H
