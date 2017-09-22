#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <algorithm>

template <typename T>
std::string toString(T value){
	std::ostringstream ss;
	ss << value;
	return ss.str();
}

std::string RadixNotation(unsigned int number, unsigned int radix){
	std::string a, s = " ";
	unsigned int t;
	while(number>0){
		t = number%radix;
		s[0] = t < 10 ? t + '0' : t - 10 + 'a';
		a += std::string(s);
		number /= radix;
	}
	std::reverse(a.begin(), a.end());
	return a;
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
