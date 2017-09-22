#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::sscanf;
using std::string;
using std::vector;

string toString(unsigned int v){
	std::ostringstream ss;
	ss << v;
	return ss.str();
}

string primeFactorization(unsigned int number){
	// vectors
	vector<unsigned int> primes, factors;

	// Find primes
	bool isPrime;
	unsigned int i, j, n=number, size;
	for(i = 2;i<=number;++i){
		// 더 이상 나눌 수가 없으면 종료
		if(n==1) break;

		isPrime = true;
		size = primes.size();
		for(j = 0;j<size;++j)
			if(i%primes[j]==0){
				isPrime = false;
				break; // 합성수
			}

		if(!isPrime) continue;
		
		// i는 소수
		j = 0;
		while(n % i == 0)
			++j, n/=i;
		primes.push_back(i);
		factors.push_back(j);
	}

	string result = "";
	size = factors.size();
	for(i=0;i<size;++i){
		if(factors[i]>=1){
			result += toString(primes[i]) + "^" + toString(factors[i]);
			if(i<size-1)
				result += " x ";
		}
	}
	return result;
}

int main(int argc, char** argv){
	if(argc<1) return -1;

	unsigned int number;
	sscanf(argv[1] ,"%u", &number);

	cout << primeFactorization(number) << endl;
}
