#include <stdio.h>
#include <string>

#include "Decoder.h"
#include "Encoder.h"


int main(int argc, char *argv[]) {
	if(argc != 2) {
		std::cerr << "Parametros invalidos" << std::endl;
		exit(0);
	}

	std::string in("../../Files/");
	in.append(argv[1]);
	std::string out(in); out.append(".cppdir/compressed");
	std::string cb(in); cb.append(".cppdir/codification");
	Encoder e(in.c_str(), out.c_str(), cb.c_str());

	in.append(".cppdir/decompressed");
	Decoder d(out.c_str(), in.c_str(), cb.c_str());

	return 0;
}
