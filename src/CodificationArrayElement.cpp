#include "CodificationArrayElement.h"

CodificationArrayElement::CodificationArrayElement(void) {
	this->used = 0;
}

CodificationArrayElement::~CodificationArrayElement(void) {
}

CodificationArrayElement::CodificationArrayElement(SYMBOL symbol) {
	this->symbol = symbol;
	this->used = 1;
}
