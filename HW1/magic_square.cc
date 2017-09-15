#include <iostream>

void make_a_fucking_magic_square(int N){
	int **square = new int*[N];
	int i,j,x,y;
	for(i=0;i<N;++i)
		square[i] = new int[N];
	for(i=0;i<N*N;++i) square[i/N][i%N] = 0;
	int v = 1;
	i = 0, j = N/2;
	while(v<=N*N){
		square[i][j]=v++;
		x = (i - 1 + N) % N, y = (j + 1) % N;
		if(!square[x][y]) i=x, j=y;
		else i = (i+1) % N;
	}
	for(i=0;i<N;++i){
		for(j=0;j<N;++j)
			std::cout << square[i][j] << " ";
		std::cout << std::endl;
	}
	for(i=0;i<N;++i)
		delete[] square[i];
	delete[] square;
}

int main(){
	int N;
	std::cin >> N;
	make_a_fucking_magic_square(N);
}
