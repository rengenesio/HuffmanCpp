#include "Encoder.h"


Encoder::Encoder(const char *file_in, const char *file_out, const char *file_cb) {
	symbols = 0;
	in = new File(file_in, "r");
	fileToMemory();
	in->close();
	memoryToFrequency();
	frequencyToNodeArray();
	huffmanEncode();
	treeToCode();
	cb = new File(file_cb, "w");
	codificationToFile();
	cb->close();
	out = new File(file_out, "w");
	memoryCompressor();
	out->close();
}

Encoder::~Encoder(void) {
	/*delete in;
	delete out;
	delete cb;*/
	/*delete[] memory;
	delete[] frequency;
	delete node_array;
	delete[] codification;*/
}

void Encoder::fileToMemory(void) {
#ifdef DEBUG
	std::cerr << std::endl << "fileToMemory():" << std::endl;
#endif
	memory = new SYMBOL[in->size + SIZEOF_SYMBOL + 10];
#ifdef DEBUG
	if(!memory) {
		std::cerr << "Erro ao alocar espaço na memória para o arquivo" << std::endl;
		exit(0);
	}
#endif
	fread(memory, in->size, 1, in->pointer);
#ifdef DEBUG
	std::cerr << "Arquivo carregado na memoria! (" << (int) in->size << " bytes)" << std::endl;
	std::cerr << "------------------------------" << std::endl;
#endif
}

void Encoder::memoryToFrequency(void) {
#ifdef DEBUG
	std::cerr << std::endl << "memoryToFrequency():" << std::endl;
#endif
	frequency = new FREQUENCY[sizeof(FREQUENCY) * POWER_BITS_CODIFICATION];
#ifdef DEBUG
	if(!frequency) {
		std::cerr << "Erro ao alocar espaço na memória para a variavel 'frequency'" << std::endl;
		exit(0);
	}
#endif
	memset(frequency, 0, sizeof(FREQUENCY) * POWER_BITS_CODIFICATION);

	for(FILE_SIZE i = 0 ; i*(SIZEOF_SYMBOL) < in->size ; i++) {
		SYMBOL symbol;
		memcpy(&symbol, memory + i, SIZEOF_SYMBOL);
		if(frequency[symbol]++ == 0)
			symbols++;
	}

	for(SIZE i = 0 ; i < POWER_BITS_CODIFICATION ; i++)
		if(!frequency[i]) {
			eof = i;
			symbols++;
			frequency[i]++;
			memset(memory + (in->size / SIZEOF_SYMBOL), eof, SIZEOF_SYMBOL);
			in->size += SIZEOF_SYMBOL;
			break;
		}

#ifdef DEBUG
	std::cerr << "FREQUENCY: symbol (frequency)" << std::endl;
	for(SIZE i = 0 ; i < POWER_BITS_CODIFICATION ; i++)
		if(frequency[i] && i != eof)
			std::cerr << (int) i << "(" << (int) frequency[i] << ")" << std::endl;
	std::cerr << "EOF: " << (int) eof << std::endl;
	std::cerr << "------------------------------" << std::endl;
#endif
}

void Encoder::frequencyToNodeArray(void) {
#ifdef DEBUG
	std::cerr << std::endl << "frequencyToNodeArray():" << std::endl;
#endif
	node_array = new NodeArray(symbols);

	for(SIZE i = 0 ; i < POWER_BITS_CODIFICATION ; i++)
		if(frequency[i])
			node_array->insertSorted(new Node(i, frequency[i]));

#ifdef DEBUG
	node_array->printArray();
	std::cerr << "------------------------------" << std::endl;
#endif
}

void Encoder::huffmanEncode(void) {
#ifdef DEBUG
	std::cerr << std::endl << "huffmanEncode():" << std::endl;
#endif

#ifdef DEBUG
	std::cerr << "symbol (frequency) + symbol (frequency)  ---> new symbol (new frequency)" << std::endl;
#endif
	while(node_array->size > 1) {
		Node *a, *b, *c;
		a = *(&(node_array->node[node_array->size-2]));
		b = *(&(node_array->node[node_array->size-1]));
		c = new Node(0, a->frequency + b->frequency, a, b);

#ifdef DEBUG
		std::cerr << (int) a->symbol << "(" << (int) a->frequency << ") + " << (int) b->symbol << "(" << (int) b->frequency << ") ---> " << (int) c->symbol << "(" << (int) c->frequency << ")" << std::endl;
#endif
		node_array->removeLastTwoNodes();
		node_array->insertSorted(c);
	}

#ifdef DEBUG
	node_array->printArray();
	std::cerr << "------------------------------" << std::endl;
#endif
}

void Encoder::treeToCode() {
#ifdef DEBUG
	std::cerr << std::endl << "treeToCode():" << std::endl;
#endif

	std::stack<Node *> s;
	codification = new Codification[symbols];
	Node *n = *(&(node_array->node[0]));
	SIZE codes = 0;

	std::string path;
	s.push(n);

	while(codes < symbols) {
		if(n->left) {
			if(!n->left->visited) {
				s.push(n);
				n->visited = 1;
				n = n->left;
				path.push_back('0');
			}
			else if(!n->right->visited) {
				s.push(n);
				n->visited = 1;
				n = n->right;
				path.push_back('1');
			}
			else {
				path.pop_back();
				n = s.top();
				s.pop();
			}
		}
		else {
			n->visited = 1;
			new (&codification[codes]) Codification(n->symbol, &path);
			path.pop_back();
			n = s.top();
			s.pop();
			codes++;
		}
	}

#ifdef DEBUG
	std::cerr << "CODIFICATION: symbol (size) code" << std::endl;
	for(SIZE i = 0 ; i < symbols ; i++)
		codification[i].print();
	std::cerr << "------------------------------" << std::endl;
#endif
}

void Encoder::codificationToFile(void) {
#ifdef DEBUG
	std::cerr << std::endl << "codificationToFile():" << std::endl;
#endif

	SIZE eof_index = 0;

	for(SIZE i = 0 ; i < symbols ; i++) {
		if(codification[i].symbol != eof) {
#ifdef DEBUG
	std::cerr << "Writing: ";
	codification[i].print();
#endif
			fwrite(&codification[i].symbol, SIZEOF_SYMBOL, 1, cb->pointer);
			fwrite(&codification[i].size, SIZEOF_SYMBOL, 1, cb->pointer);
			fwrite(codification[i].code->c_str(), sizeof(unsigned char), codification[i].size, cb->pointer);
		}
		else
			eof_index = i;
	}
#ifdef DEBUG
	std::cerr << "Writing: ";
	codification[eof_index].print();
#endif
	fwrite(&codification[eof_index].symbol, SIZEOF_SYMBOL, 1, cb->pointer);
	fwrite(&codification[eof_index].size, SIZEOF_SYMBOL, 1, cb->pointer);
	fwrite(codification[eof_index].code->c_str(), sizeof(unsigned char), codification[eof_index].size, cb->pointer);
#ifdef DEBUG
	std::cerr << "------------------------------" << std::endl;
#endif
}

void Encoder::memoryCompressor(void) {
#ifdef DEBUG
	std::cerr << std::endl << "memoryCompressor():" << std::endl;
#endif

	std::bitset<BYTE_BIT> buffer;
	unsigned int bits = 0;

	for(unsigned int i = 0 ; i < in->size / SIZEOF_SYMBOL ; i++) {
		for(unsigned int j = 0 ; j < symbols ; j++) {
			if(memory[i] == codification[j].symbol) {
				//unsigned int tam_string = codification[j].size;
				//for(unsigned int k = 0 ; k < tam_string ; k++) {
				for(std::string::iterator it = codification[j].code->begin() ; it != codification[j].code->end() ; it++) {
					//if(codification[j].code->at(k) == '1') {
					if(*it == '1') {
						//SET_BIT(&buffer, bits);
						buffer.set(BYTE_BIT - 1 -bits, 1);
					}
					else {
						//CLEAR_BIT(&buffer, bits);
						buffer.set(BYTE_BIT - 1 -bits, 0);
					}

					if(++bits == BYTE_BIT) {
						fwrite(&buffer, 1, 1, out->pointer);
						bits = 0;
					}
				}
				break;
			}
		}
	}
	if(bits) {
		fwrite(&buffer, 1, 1, out->pointer);
	}
#ifdef DEBUG
	std::cerr << "------------------------------" << std::endl;
#endif
}
