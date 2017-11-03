#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <stdexcept>
#include "simple_int_set.h"

std::tuple<bool, char, std::set<int>, std::set<int>> getInput(std::istream& is);
bool getIntSetFromString(std::set<int>& int_set, const std::string& str);

int main() {
	while (true)
	{
		bool result;
		char operation;
		std::set<int> s1, s2, new_set;
		std::tie(result, operation, s1, s2) = getInput(std::cin);
		if (!result) break;
		switch (operation) {
		case '+':
			new_set = SimpleIntSet::SetUnion(s1, s2);
			break;
		case '-':
			new_set = SimpleIntSet::SetDifference(s1, s2);
			break;
		case '*':
			new_set = SimpleIntSet::SetIntersection(s1, s2);
			break;
		}
		std::cout << "{";
		for (int x : new_set)
			std::cout << " " << x;
		std::cout << " }" << std::endl;
	}
	return 0;
}

std::tuple<bool, char, std::set<int>, std::set<int>> getInput(std::istream& is) {
	std::set<int> set0, set1;
	std::string str;
	std::getline(is, str);
	
	size_t pos = -1;

	// Find the position of vaild operator ( +, -, * ).
	while ((pos = str.find_first_of("+-*", pos + 1)) != std::string::npos 
		&& pos + 1 < str.size() && isdigit(str[pos + 1]));

	// If no operators exists, return false;
	if(pos== std::string::npos)
		return std::make_tuple(false, NULL, set0, set1);

	bool success = true;
	success &= getIntSetFromString(set0, str.substr(0, pos));
	success &= getIntSetFromString(set1, str.substr(pos + 1, str.size() - pos - 1));

	return std::make_tuple(success, str[pos], set0, set1);
}

bool getIntSetFromString(std::set<int>& int_set, const std::string& str) {
	// Find the positions of a pair of braces in 'str'.
	size_t l = str.find_first_of('{');
	size_t r = str.find_first_of('}', l+1);
	
	// Check if they appear in 'str'.
	if (l == std::string::npos || r == std::string::npos || l >= r)
		return false;
	
	// Declare temporary variables.
	int temp_n;
	std::string temp;
	std::stringstream ss(str.substr(l+1, r-l-1));
	while (true) {
		try {
			// Get the tokenized string first.
			ss >> temp;
			// If there is no content to fetch, terminate the function.
			if (ss.fail())	return true;
			// Convert the string to an integer type.
			temp_n = std::stoi(temp);
			// Append the value into the set.
			int_set.insert(temp_n);
		}
		catch (const std::invalid_argument& ia) {return false; /* When something strange input comes in, return false. */}
	}
	return true;
}

/*
int state;

0 - 왼쪽 중괄호 필요 --> { 만나면 끝
1 - 왼쪽 집합 흡수중 --> } 만나면 끝
2 - 방금 왼쪽 중괄호 끝남 --> OP 먹고 { 만나면 끝
3 - 오른쪽 집합 흡수중 --> } 만나면 끝

*/