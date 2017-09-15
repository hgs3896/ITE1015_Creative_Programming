#include <iostream>

void swap(int &a, int &b){
	int c = a;	a = b;	b = c;
}

void quick_sort_iterative(int *arr, unsigned int N, unsigned int firstIndex=0) {
	if (N <= 1) return;
	int *stack = new int[2*N];
	int front, end, l, r, pivot, top = 0;
	stack[top++] = firstIndex;
	stack[top++] = firstIndex + N - 1;
	while (top) {
		end = stack[--top];
		front = stack[--top];
		l = front;
		r = end - 1;
		pivot = end;
		while (l <= r) {
			while (arr[l] < arr[pivot]) ++l;
			while (arr[r] > arr[pivot]) --r;
			if (l > r) break;
			swap(arr[l], arr[r]);
		}
		swap(arr[l], arr[pivot]);
		if (l - front > 1) {
			stack[top++] = front;
			stack[top++] = l - 1;
		}
		if (end - l > 1) {
			stack[top++] = l + 1;
			stack[top++] = end;
		}
	}
	delete[] stack;
}

int main(){
	unsigned int N;
	std::cin >> N;
	int *arr = new int[N];
	int i;
	for(i=0;i<N;++i)
		std::cin >> arr[i];
	quick_sort_iterative(arr, N);
	for(i=0;i<N;++i)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
	delete[] arr;
}
