#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <algorithm>

std::string RadixNotation(unsigned int number, unsigned int radix){
	std::string s;
	unsigned int r;
	do{
		r = number%radix;
		char buffer[3];
		sprintf(buffer, "%c", (r < 10 ? r + '0' : r + 'a' - 10));
		s += std::string(buffer);
		number /= radix;
	}while(number>0);
	std::reverse(s.begin(), s.end());
	return s;
}

int main(int argc, char** argv){
	if(argc<2) return -1;
	unsigned int radix;
	std::sscanf(argv[1], "%u", &radix);
	unsigned int number;
	if(radix<2 || radix>36) return -1;
	for(int i=2;i<argc;++i){
		std::sscanf(argv[i], "%u", &number);
		std::cout << RadixNotation(number, radix) << std::endl;
	}
	return 0;
}
