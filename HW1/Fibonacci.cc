#include <iostream>

bool printed[45];

unsigned int fibo(const unsigned int n){
	int result = n<=2 ? 1 : fibo(n-2) + fibo(n-1);

	if(!printed[n-1]){
		std::cout << result << " ";
		printed[n-1]=true;
	}

	return result;
}

int main(){
	int i, n;
	std::cin >> n;
	fibo(n);
	std::cout << std::endl;
}
