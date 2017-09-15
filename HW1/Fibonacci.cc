#include <iostream>

unsigned long long *fib;

unsigned long long fibo(const unsigned int n){
	if(n<=2){
		if(!fib[n]){
			std::cout << "1 ";
			fib[n]=1ull;
		}
		return fib[n];
	}
	if(!fib[n-2]) fib[n-2] = fibo(n-2);
	if(!fib[n-1]) fib[n-1] = fibo(n-1);
	fib[n] = fib[n-2] + fib[n-1];
	std::cout << fib[n] << " ";
	return fib[n];
}

int main(){
	int i, n;
	std::cin >> n;

	try{
		fib = new unsigned long long[n+1];
		for(i=0;i<=n;++i) fib[i]=0ull;

		fibo(n);

		delete[] fib;
	}catch(std::bad_alloc e){
	}
	std::cout << std::endl;
}
