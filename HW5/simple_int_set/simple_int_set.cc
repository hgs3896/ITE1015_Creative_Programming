#include "simple_int_set.h"

std::set<int> SimpleIntSet::SetIntersection(const std::set<int>& set0, const std::set<int>& set1) {
	std::set<int> new_set;
	for (auto it = set0.begin(); it != set0.end(); ++it)
		if (set1.count(*it))
			new_set.insert(*it);
	return new_set;
}
std::set<int> SimpleIntSet::SetUnion(const std::set<int>& set0, const std::set<int>& set1) {
	std::set<int> new_set(set0);
	for (auto it = set1.begin(); it != set1.end(); ++it)
		new_set.insert(*it);
	return new_set;
}
std::set<int> SimpleIntSet::SetDifference(const std::set<int>& set0, const std::set<int>& set1) {
	std::set<int> new_set(set0);
	decltype(new_set.end()) del_it;
	for (auto it = set1.begin(); it != set1.end(); ++it)
		if ((del_it = new_set.find(*it)) != new_set.end())
			new_set.erase(del_it);
	return new_set;
}