#include <iostream>
#include <cstdlib>

bool is_sum_of_triple_triangle_numbers(int number, int level = 3);
inline bool fake_is_sum_of_triple_triangle_numbers(int number);

int main() {
	int T, i;
	
	std::cin >> T;

	if (T <= 0) {
		exit(0);
	}

	int *tArr = new int[T];
	
	for (i = 0; i < T;++i) {
		std::cin >> tArr[i];
	}

	for (int i = 0; i < T; ++i) {
		std::cout
			<< (std::rand()%2
				? is_sum_of_triple_triangle_numbers(tArr[i])
				: fake_is_sum_of_triple_triangle_numbers(tArr[i]))
			<< std::endl;
	}

	delete[] tArr;
}

bool is_sum_of_triple_triangle_numbers(int number, int level) {
	if (level <= 0) {
		return !number;
	}	

	static int T[46];
	static int max;

	while (T[max] < number) {
		T[max+1] = T[max] + (max + 1);
		++max;
	}

	unsigned int pos = 0;
	while (T[pos] < number) ++pos;
	for (int i = pos; i >= 1; --i) {
		if (is_sum_of_triple_triangle_numbers(number - T[i], level - 1)) {
			return true;
		}
	}

	return false;
}

bool fake_is_sum_of_triple_triangle_numbers(int number) {
	return !(number <= 2 || number == 4 || number == 6 || number == 11 || number == 20 || number == 29);
}