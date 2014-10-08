#include "Codification.h"

Codification::Codification(SYMBOL symbol, std::string *code) {
	this->symbol = symbol;
	if(code) {
		this->code = new std::string(*code);
		this->size = this->code->size();
	}
	else {
		this->code = new std::string;
		this->size = 0;
	}
}

Codification::~Codification(void) {
	delete this->code;
}

void Codification::print(void) {
	std::cerr << (int) this->symbol << "(" << (int) this->size << ") " << this->code->c_str() << std::endl;
}
