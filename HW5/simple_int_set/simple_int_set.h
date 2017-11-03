#ifndef __H_SIMPLE_INT_SET_
#define __H_SIMPLE_INT_SET_

#include <set>
class SimpleIntSet {
public:
	static std::set<int> SetIntersection(const std::set<int>& set0, const std::set<int>& set1);
	static std::set<int> SetUnion(const std::set<int>& set0, const std::set<int>& set1);
	static std::set<int> SetDifference(const std::set<int>& set0, const std::set<int>& set1);
};

#endif
