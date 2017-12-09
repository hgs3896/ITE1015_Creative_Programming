#include <iostream>
#include <vector>
#include <thread>
#include <random>
using namespace std;

int doMonti(int strategy, int rep, int doors);

int main() {
	int strategy, rep, success;
	cin >> strategy >> rep;
	success = doMonti(strategy, rep, 3);
	cout.precision(3);
	cout << double(100 * success) / rep << "% (" << success << " / " << rep << ")" << endl;
	return 0;
}

int doMonti(int strategy, int rep, int doors) {
	int success = 0;
	if (strategy <= 0 || strategy > 3) {
		return -1;
	}

	void action1(int N, bool* result);
	void action2(int N, bool* result);
	void action3(int N, bool* result);

	void(*func_arr[3])(int, bool*) = { action1, action2, action3 };

	vector<thread> threads;
	static const int max_thread_number = 2 * 4;
	bool *arr = new bool[max_thread_number];
	int i, j, k, r;

	k = rep / max_thread_number;
	for (i = 0; i < k; ++i) {
		for (j = 0; j < max_thread_number; ++j)
			threads.push_back(thread(func_arr[strategy - 1], doors, arr + j));
		for (auto& thread : threads)
			thread.join();
		threads.clear();
		for (j = 0; j < max_thread_number; ++j)
			success += arr[j], arr[j] = false;
	}

	r = rep % max_thread_number;
	for (j = 0; j < r; ++j)
		threads.push_back(thread(func_arr[strategy - 1], doors, arr + j));
	for (auto& thread : threads)
		thread.join();
	threads.clear();
	for (j = 0; j < r; ++j)
		success += arr[j], arr[j] = false;

	delete[] arr;
	return success;
}

void action1(int N, bool* result) {
	static random_device rd;
	static mt19937_64 rng(rd());
	uniform_int_distribution<__int64> dist(1, N);
	int g, c;
	g = dist(rng);
	c = dist(rng);	
	*result = c == g;
}

void action2(int N, bool* result) {
	static random_device rd;
	static mt19937_64 rng(rd());
	uniform_int_distribution<__int64> dist(1, N);
	int c, g, m, l_c;
	g = dist(rng);
	c = dist(rng);
	while ((m = dist(rng)) == g || m == c);
	while ((l_c = dist(rng)) == c || l_c == m);
	*result = l_c == g;
}

void action3(int N, bool* result) {
	static random_device rd;
	static mt19937_64 rng(rd());
	uniform_int_distribution<__int64> dist(1, N);
	int g, c, m, l_c;
	g = dist(rng);
	c = dist(rng);
	while ((m = dist(rng)) == g || m == c);
	while ((l_c = dist(rng)) == m);
	*result = l_c == g;
}