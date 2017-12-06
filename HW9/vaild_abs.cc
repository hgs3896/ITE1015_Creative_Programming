#include <string>
#include <vector>
#include <iostream>

int main() {
	int T;
	std::string str;
	std::vector<bool> res;
	std::cin >> T;
	while (T--) {
		std::cin >> str;
		int result = 0;
		for (const auto& c : str) {
			if (c == '<') ++result;
			else if (c == '>') --result;
		}
		res.push_back(result==0);
	}
	for (bool x : res) {
		std::cout << (x ? "YES" : "NO") << std::endl;
	}
	return 0;
}