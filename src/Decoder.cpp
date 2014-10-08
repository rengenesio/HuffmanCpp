#include "Decoder.h"

Decoder::Decoder(const char *file_in, const char *file_out, const char *file_cb) {
	symbols = 0;
	max_code = 0;
	cb = new File(file_cb, "r");
	fileToCode();
	cb->close();
	eof = codification[symbols-1].symbol;
	codeToTreeArray();
	in = new File(file_in, "r");
	out = new File(file_out, "w");
	huffmanDecode();
	in->close();
	out->close();
}

void Decoder::fileToCode(void) {
#ifdef DEBUG
	std::cerr << std::endl << "fileToCode():" << std::endl;
#endif
	bool read = true;
	codification = new Codification[POWER_BITS_CODIFICATION];
	do {
		fread(&codification[symbols].symbol, SIZEOF_SYMBOL, 1, cb->pointer);
		fread(&codification[symbols].size, SIZEOF_SYMBOL, 1, cb->pointer);
		char *code = new char[codification[symbols].size + 1];
		read = fread(code, sizeof(unsigned char), codification[symbols].size, cb->pointer);
		codification[symbols].code = new std::string(code);
		if(codification[symbols].size > max_code)
			max_code = codification[symbols].size;
		symbols++;
	} while(read);
	symbols--;
#ifdef DEBUG
	std::cerr << "CODIFICATION: symbol (size) code" << std::endl;
	for(SIZE i = 0 ; i < symbols ; i++)
		codification[i].print();
	std::cerr << "------------------------------" << std::endl;
#endif
}

void Decoder::codeToTreeArray(void) {
#ifdef DEBUG
	std::cerr << std::endl << "codeToTreeArray():" << std::endl;
#endif
	tree_array = new CodificationArrayElement[power(2, (max_code + 1))];

	for(SIZE i = 0 ; i < symbols ; i++) {
		SIZE index = 0;
		//for(SIZE j = 0 ; j < codification[i].size ; j++) {
		for(std::string::iterator it = codification[i].code->begin() ; it != codification[i].code->end() ; it++) {
			index <<= 1;
			//if(codification[i].code->at(j) == '0')
			if(*it == '0')
				index += 1;
			else
				index += 2;
		}
		tree_array[index] = CodificationArrayElement(codification[i].symbol);
	}
#ifdef DEBUG
	std::cerr << "TREE_ARRAY:" << std::endl;
	for(SIZE i = 0 ; i < power(2, (max_code + 1)) ; i++) {
		if(tree_array[i].used)
			std::cerr << "i: " << (int) i << " -> " << (int) tree_array[i].symbol << std::endl;
	}
	std::cerr << "------------------------------" << std::endl;
#endif
}

void Decoder::huffmanDecode(void) {
#ifdef DEBUG
	std::cerr << std::endl << "huffmanDecode():" << std::endl;
#endif
	bool feof = 0;
	SIZE index = 0;

	while(!feof) {
		BYTE buffer;
		fread(&buffer, 1, 1, in->pointer);
		for(BYTE j = 0 ; j < BYTE_BIT ; j++) {
			index <<= 1;
			if((GET_BIT(&buffer, j)) == 0)
				index += 1;
			else
				index += 2;

			if(tree_array[index].used) {
				if(tree_array[index].symbol != eof) {
#ifdef DEBUG
					std::cerr << "Writing: " << (int) tree_array[index].symbol << std::endl;
#endif
					fwrite(&tree_array[index].symbol, SIZEOF_SYMBOL, 1, out->pointer);
				}
				else {
					return;
				}
				index = 0;
			}
		}
	}
#ifdef DEBUG
	std::cerr << "------------------------------" << std::endl;
#endif
}

unsigned int Decoder::power(unsigned int a, unsigned int b) {
	unsigned int pow = 1;
	for (unsigned int i = 0 ; i < b ; i++)
		pow *= a;

	return pow;
}
