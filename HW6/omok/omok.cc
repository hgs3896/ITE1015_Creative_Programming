#include "omok.h"

Omok::Omok() : turn_(BLACK) {
	for(int i = 0;i<GROUND_SIZE;++i)
		for (int j = 0; j<GROUND_SIZE; ++j)
			map[i][j]=0;
}

int Omok::Put(int x, int y) {
	if (!turn_ || !inRange(x,y) || map[y][x]) {
		return Omok::NOBODY;
	}
	map[y][x] = turn_;
	turn_ = -turn_;
	return map[y][x];
}

int Omok::IsOmok() const {
	static const int xx[8] = {1,1,0,-1,-1,-1,0,1};
	static const int yy[8] = {0,1,1,1,0,-1,-1,-1};
		
	for (int i = 0; i < GROUND_SIZE; ++i) {
		for (int j = 0; j < GROUND_SIZE; ++j) {
			if (map[i][j]) {
				int cnt, next_x, next_y;
				for (int k = 0; k < 8; ++k) {
					cnt = 0;
					next_x = j, next_y = i;
					for (int p = 0; p < 4; ++p){
						next_x += xx[k], next_y += yy[k];
						if (!inRange(next_x, next_y) || map[next_y][next_x] != map[i][j]) {
							break;
						}
						++cnt;
					}
					if (cnt < 4) {
						continue;
					}
					next_x += xx[k], next_y += yy[k];
					if (!inRange(next_x, next_y) || map[next_y][next_x] != map[i][j]) {
						return -Turn();
					}
				}
			}
		}
	}

	return NOBODY;
}

int Omok::Turn() const {
	switch (turn_)
	{
	case BLACK:
		return BLACK;
	case WHITE:
		return WHITE;
	default:
		return NOBODY;
	}
}

bool Omok::inRange(int x, int y) const {
	return x>=0 && x<GROUND_SIZE && y >= 0 && y<GROUND_SIZE;
}

std::ostream& operator<<(std::ostream& os, const Omok& omok) {
	for (int i = 0; i < Omok::GROUND_SIZE; ++i) {
		for (int j = 0; j < Omok::GROUND_SIZE; ++j) {
			switch (omok.map[i][j]) {
			case Omok::BLACK:
				os << "o";
				break;
			case Omok::WHITE:
				os << "x";
				break;
			case Omok::NOBODY:
				os << ".";
				break;
			}
		}
		os << std::endl;
	}
	return os;
}