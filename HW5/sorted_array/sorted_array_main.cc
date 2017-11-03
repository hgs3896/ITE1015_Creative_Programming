#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "sorted_array.h"

void printArray(const std::vector<int> v);

int main() {
	SortedArray arr;
	std::string cmd;
	while (std::getline(std::cin, cmd)) {
		if (cmd == "ascend")
			printArray(arr.GetSortedAscending());
		else if (cmd == "descend")
			printArray(arr.GetSortedDescending());
		else if (cmd == "max")
			std::cout << arr.GetMax() << std::endl;
		else if (cmd == "min")
			std::cout << arr.GetMin() << std::endl;
		else if (cmd == "quit")
			break;
		else
		{
			int n;
			bool vaild = true;
			std::stringstream ss(cmd);
			std::string temp;
			while (true) {
				ss >> temp;
				if (ss.fail()) break;
				try { n = stoi(temp); }
				catch (const std::invalid_argument& ia) { return 0; /* 규칙 외 입력은 종료한다. */ }
				arr.AddNumber(n);
			}
		}
	}
}

void printArray(const std::vector<int> v) {
	for (int x : v)	std::cout << x << " ";
	std::cout << std::endl;
}