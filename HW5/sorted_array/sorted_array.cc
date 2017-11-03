#include "sorted_array.h"
SortedArray::SortedArray() {}
SortedArray::~SortedArray() {}

void SortedArray::AddNumber(int num) {
	numbers.push_back(num);
	std::sort(numbers.begin(), numbers.end());
}
std::vector<int> SortedArray::GetSortedAscending() const {
	return numbers;
}
std::vector<int> SortedArray::GetSortedDescending() const {
	std::vector<int> v(numbers);
	std::reverse(v.begin(), v.end());
	return v;
}
int SortedArray::GetMax() const {
	if (numbers.size() == 0)
		return 0;
	return numbers[numbers.size() - 1];
}
int SortedArray::GetMin() const {
	if (numbers.size() == 0)
		return 0;
	return numbers[0];
}