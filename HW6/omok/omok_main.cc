#include <iostream>
#include "omok.h"

using std::cin;
using std::cout;

int main() {
	Omok game;
	int x, y;
	int winner;
	do {
		cin >> x >> y;
		if(!game.Put(x, y)) {
			cout << "Can not be placed there" << std::endl;
		}
	} while (!(winner = game.IsOmok()));
	cout << game;
	cout << "Winner: " << (winner == Omok::BLACK ? "Black" : "WHITE") << " player " << std::endl;
	return 0;
}