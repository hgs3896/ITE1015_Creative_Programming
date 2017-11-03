#ifndef __H_SORTED_ARRAY_
#define __H_SORTED_ARRAY_
#include <vector>
#include <algorithm>

class SortedArray{
public:
	SortedArray();
	~SortedArray();

	void AddNumber(int num);
	std::vector<int> GetSortedAscending() const;
	std::vector<int> GetSortedDescending() const;
	int GetMax() const;
	int GetMin() const;
private:
	std::vector<int> numbers;
};

#endif