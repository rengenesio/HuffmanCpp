#ifndef DECODER_H
#define DECODER_H


#include <math.h>

#include "Codification.h"
#include "CodificationArrayElement.h"
#include "File.h"

class Decoder {

public:
	Decoder(const char *file_in, const char *file_out, const char *file_cb);
	void fileToCode(void);
	void codeToTreeArray(void);
	void huffmanDecode(void);
	unsigned int power (unsigned int a, unsigned int b);

	File *in, *out, *cb;
	SIZE symbols;
	SYMBOL max_code;
	SYMBOL eof;
	Codification *codification;
	CodificationArrayElement *tree_array;

};

#endif // DECODER_H
