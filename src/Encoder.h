#ifndef ENCODER_H
#define ENCODER_H


#include <bitset>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <vector>

#include "Codification.h"
#include "Defines.h"
#include "File.h"
#include "Node.h"
#include "NodeArray.h"


#define IN		1
#define OUT		2
#define CB		3


class Encoder {

public:
	Encoder(const char *file_in, const char *file_out, const char *file_cb);
	~Encoder(void);
	void openFile(char *file, uint8_t type);
	void closeFile(uint8_t type);
	void fileToMemory(void);
	void memoryToFrequency(void);
	void frequencyToNodeArray(void);
	void huffmanEncode(void);
	void treeToCode(void);
	void codificationToFile(void);
	void memoryCompressor(void);

	File *in, *out, *cb;
	SYMBOL *memory;
	FREQUENCY *frequency;
	SIZE symbols;
	SYMBOL eof;
	NodeArray *node_array;
	Codification *codification;

};

#endif // ENCODER_H
