#include "simple_int_set.h"
#include <iostream>
#include <algorithm>
using namespace std;
void SimpleIntSet::sortElements()
{
	sort(mElements, mElements + mElementCount);
}
void SimpleIntSet::uniqueElements() {
	int *tempArr = new int[mElementCount];
	int k = 1;
	tempArr[0] = mElements[0];
	for (int i = 1; i < mElementCount; ++i) {
		if (mElements[i] == mElements[i - 1])
			continue;
		tempArr[k++] = mElements[i];
	}
	delete[] mElements;
	mElements = tempArr;
	mElementCount = k;
}
SimpleIntSet::SimpleIntSet(): mElementCount(0), mElements(NULL) {}
SimpleIntSet::SimpleIntSet(int *_elements, int _count): mElementCount(_count) {
	if(mElementCount<=0) 
		return;
	mElements = new int[mElementCount];
	for (int i = 0; i < mElementCount; ++i)
		mElements[i] = _elements[i];
	sortElements();
	uniqueElements();
}
SimpleIntSet::~SimpleIntSet() {
	delete[] mElements;
}
int* SimpleIntSet::elements() const // return sorted array
{
	return mElements;
}
int SimpleIntSet::elementCount() const
{
	return mElementCount;
}
SimpleIntSet* SimpleIntSet::unionSet(SimpleIntSet& _operand) {
	int s1 = this->elementCount(), s2 = _operand.elementCount();
	int *arr = new int[s1+s2];
	int l=0, r=0, k=0;
	while (l < s1 && r < s2) {
		if (mElements[l] < _operand.mElements[r])
			arr[k] = mElements[l++];
		else if (mElements[l] > _operand.mElements[r])
			arr[k] = _operand.mElements[r++];
		else
			arr[k] = mElements[l], ++l, ++r;
		k++;
	}
	while (l<s1)
		arr[k++] = mElements[l++];
	while (r<s2)
		arr[k++] = _operand.mElements[r++];

	delete[] mElements;
	mElements = arr;
	mElementCount = k;
	return this;
}
SimpleIntSet* SimpleIntSet::differenceSet(SimpleIntSet& _operand) {
	int s1 = this->elementCount(), s2 = _operand.elementCount();
	int *arr = new int[s1];
	int l = 0, r = 0, k = 0;
	while (l<s1 && r<s2) {
		if (mElements[l] < _operand.mElements[r])
			arr[k++] = mElements[l++];
		else if (mElements[l] > _operand.mElements[r])
			++r;
		else
			++l, ++r;
	}
	while (l<s1)
		arr[k++] = mElements[l++];

	delete[] mElements;
	mElements = arr;
	mElementCount = k;
	return this;
}
SimpleIntSet* SimpleIntSet::intersectSet(SimpleIntSet& _operand) {
	int s1 = this->elementCount(), s2 = _operand.elementCount();
	int *arr = new int[s1];
	int l = 0, r = 0, k = 0;
	while (l<s1 && r<s2) {
		if (mElements[l] < _operand.mElements[r])
			++l;
		else if (mElements[l] > _operand.mElements[r])
			++r;
		else
			arr[k++] = mElements[l], ++l, ++r;
	}

	delete[] mElements;
	mElements = arr;
	mElementCount = k;
	return this;
}
void SimpleIntSet::printSet() {
	cout << "{ ";
	for (int i = 0; i < mElementCount; ++i)
		cout << mElements[i] << " ";
	cout << " }" << endl;
}