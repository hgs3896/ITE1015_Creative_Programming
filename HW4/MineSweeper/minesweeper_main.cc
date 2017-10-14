#include "minesweeper.h"
using namespace std;

int main(void) {
	Minesweeper* minesweeper = new Minesweeper();
	while (true) {
		string command;
		stringstream st;

		getline(cin, command);
		if (command.find(":set") != string::npos) {
			int w, h;
			st << command.substr(4);			
			st >> w >> h;

			vector<string> args;
			for (int i = 0; i < h; ++i) {
				string line;
				getline(cin, line);
				args.push_back(line);
			}

			minesweeper->setMap(w, h, args);
			minesweeper->printMapWithNumbers();
		}
		else if (command.find(":toggle") != string::npos) {
			int x, y;
			st << command.substr(7);
			st >> x >> y;
			
			if (minesweeper->playing())
				continue;
			
			minesweeper->toggleMine(x, y);
			minesweeper->printMapWithNumbers();
		}
		else if (command.find(":touch") != string::npos) {
			int x, y;
			st << command.substr(6);
			st >> x >> y;

			if (!minesweeper->playing())
				continue;
			
			if (!minesweeper->touchMap(x, y))
				cout << "DEAD(" << minesweeper->touchCount() << ")" << endl;			
		}
		else if (command.find(":play") != string::npos) {
			if (minesweeper->setPlay())
				minesweeper->printMap();
		}
		else if (command.find(":quit") != string::npos) {
			break;
		}
	}
	delete minesweeper;
}