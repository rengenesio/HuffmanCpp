#include "File.h"

File::File(const char *file, const char *arg) {
	pointer = fopen(file, arg);
#ifdef DEBUG
	if(pointer == NULL) {
		std::cerr << "Erro ao abrir o arquivo " << file << "(" << arg << ")" << std::endl;
		exit(0);
	}
#endif
	fseek(pointer, 0 , SEEK_END);
	size = ftell(pointer);
	rewind(pointer);
}

File::~File(void) {
}

void File::close(void) {
	fclose(pointer);
}
