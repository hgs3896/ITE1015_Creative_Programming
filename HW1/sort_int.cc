#include <iostream>

void swap(int &a, int &b){
	int c = a;	a = b;	b = c;
}

void sort(int *arr, unsigned int N) {
	if (N <= 1) return;
	int i, j;
	for(i=0;i<N-1;++i)
		for(j=i+1;j<N;++j)
			if(arr[i]>arr[j])
				swap(arr[i],arr[j]);
}

int main(){
	unsigned int N, i;

	std::cin >> N;
	int *arr = new int[N];
	
	for(i=0;i<N;++i) std::cin >> arr[i];
	
	// Sort
	sort(arr, N);

	for(i=0;i<N;++i) std::cout << arr[i] << " ";
	std::cout << std::endl;

	delete[] arr;
}
