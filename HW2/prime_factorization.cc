#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::sscanf;
using std::sprintf;
using std::string;
using std::vector;

string primeFactorization(unsigned int number){
	// vectors
	vector<unsigned int> primes, factors;

	// Find primes
	bool isPrime;
	unsigned int i, j, n=number, size;
	for(i = 2;i<=number;++i){
		// Divide until n becomes 1.
		if(n==1) break;
		// Suppose i is a prime number.
		isPrime = true;
		size = primes.size();
		// Check whether i is divisible by primes[j] in prime number lists(primes).
		for(j = 0;j<size;++j)
			if(i%primes[j]==0){
				// If i is divisible by any of prime number in the prime list,
				// falsify the isPrime value and break.
				isPrime = false;
				break;
			}

		// Since i is not a prime number, continue to check the others.
		if(!isPrime)
			continue;

		// From here, i is a newly found prime number not in our prime lists.
		j = 0;
		while(n % i == 0)
			++j, n/=i;
		// Add new prime number.
		primes.push_back(i);
		// Add how many times the prime number has been multiplied to the given value.
		factors.push_back(j);
	}

	// Make a string format
	string result;
	size = factors.size();
	for(i=0;i<size;++i){
		if(factors[i]>=1){
			char buffer[100];
			sprintf(buffer, "%u^%u", primes[i], factors[i]);
			result += string(buffer);
			if(i<size-1)
				result += " x ";
		}
	}
	return result;
}

int main(int argc, char** argv){
	if(argc<1)
		return -1;
	unsigned int number;
	sscanf(argv[1] ,"%u", &number);
	cout << primeFactorization(number) << endl;
}
