#include <iostream>
#include <vector>
#include <thread>
#include <random>
using namespace std;

typedef long long ll;

ll doMonti(int strategy, ll rep, ll doors);

int main() {
	int strategy;
	ll rep, doors, success;
	cin >> strategy >> rep >> doors;
	success = doMonti(strategy, rep, doors);
	if(success==-1){
		exit(0);
	}
	cout.precision(3);
	cout << 100 * success / static_cast<long double>(rep) << "% (" << success << " / " << rep << ")" << endl;
	return 0;
}

ll doMonti(int strategy, ll rep, ll doors) {
	ll success = 0;
	if (strategy <= 0 || strategy > 3) {
		return -1;
	}

	void action1(ll N, bool* result);
	void action2(ll N, bool* result);
	void action3(ll N, bool* result);

	void(*func_arr[3])(ll, bool*) = { action1, action2, action3 };

	vector<thread> threads;
	static const int max_thread_number = 2 * 4;
	bool *arr = new bool[max_thread_number];
	int i, j;
	ll k, r;

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

void action1(ll N, bool* result) {
	static random_device rd;
	static mt19937_64 rng(rd());
	uniform_int_distribution<ll> dist(1, N);
	ll g, c;
	g = dist(rng);
	c = dist(rng);	
	*result = c == g;
}

void action2(ll N, bool* result) {
	static random_device rd;
	static mt19937_64 rng(rd());
	uniform_int_distribution<ll> dist(1, N);
	ll c, g, m, l_c;
	g = dist(rng);
	c = dist(rng);
	while ((m = dist(rng)) == g || m == c);
	while ((l_c = dist(rng)) == c || l_c == m);
	*result = l_c == g;
}

void action3(ll N, bool* result) {
	static random_device rd;
	static mt19937_64 rng(rd());
	uniform_int_distribution<ll> dist(1, N);
	ll g, c, m, l_c;
	g = dist(rng);
	c = dist(rng);
	while ((m = dist(rng)) == g || m == c);
	while ((l_c = dist(rng)) == m);
	*result = l_c == g;
}
