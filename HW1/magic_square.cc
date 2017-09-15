#include <iostream>

void make_a_fucking_magic_square(unsigned int** square, int N){
	int i,j,x,y,v;

	// Initialization
	for(i=0;i<N*N;++i)	square[i/N][i%N] = 0;
	v = 1, i = 0, j = N/2;
	
	// Fill in the fucking magic square the numbers from 1 to N*N.
	while(v<=N*N){
		// Fill in the number(the variable v).
		square[i][j]=v++;
		// The ordered pair (x,y) is the next point at which the next number of the square should be located.
		x = (i - 1 + N) % N, y = (j + 1) % N;
		if(!square[x][y]) i=x, j=y;
		else i = (i+1) % N;
	}
}

int main(){
	int i, N;
	// Get an input data.
	std::cin >> N;

	// Check if N is something wrong.
	if(N<=0 || N%2==0) return 0;

	try{
		// Allocation
		unsigned int **square = new unsigned int*[N];
		for(i=0;i<N;++i) square[i] = new unsigned int[N];

		// Make a fucking magic square.
		make_a_fucking_magic_square(square, N);

		// Printing
		for(i=0;i<N*N;++i){
			std::cout << square[i/N][i%N];
			if((i+1)%N==0)	std::cout << std::endl;
			else 			std::cout << " ";
		}

		// Deallocation
		for(i=0;i<N;++i){
			delete[] square[i];
			square[i] = NULL;
		}
		delete[] square;
		square = NULL;
	}catch(std::bad_alloc& e){
		// The allocation was not that good.
		std::cout << e.what();
	}
}
