#include "binary_search.h"
#include <algorithm>
using namespace std;
inline void BinarySearch::sortArray() {
	sort(mArray, mArray+mArrayCount);
}
BinarySearch::BinarySearch(): mArray(NULL), mArrayCount(0){}
BinarySearch::BinarySearch(int *_array, int _arrayCount) : mArrayCount(_arrayCount){
	if (mArrayCount <= 0) return;
	mArray = new int[mArrayCount];
	for (int i = 0; i < mArrayCount; ++i)
		mArray[i] = _array[i];
	sortArray();
}
BinarySearch::~BinarySearch() {
	delete[] mArray;
}
int BinarySearch::getIndex(int _element) {
	int m, l = 0, r = mArrayCount - 1;
	while (l <= r) {
		m = (l + r) / 2;
		if (mArray[m] == _element)
			return m;
		else if (mArray[m] < _element)
			l = m+1;
		else
			r = m-1;
	}
	return -1;
}