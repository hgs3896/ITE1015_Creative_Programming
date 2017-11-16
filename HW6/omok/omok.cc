#include "omok.h"

Omok::Omok() : turn_(BLACK), min_pos(GROUND_SIZE*GROUND_SIZE-1), max_pos(0) {
	map = new int*[GROUND_SIZE]();
	for (int i = 0; i < GROUND_SIZE; ++i)
		map[i] = new int[GROUND_SIZE]();
}

Omok::~Omok() {
	for (int i = 0; i < GROUND_SIZE; ++i)
		delete[] map[i];
	delete[] map;
	map = nullptr;
}

int Omok::Put(int x, int y) {
	/*
	 * 1. 턴이 이미 종료되었거나
	 * 2. 범위 밖에 돌을 놓으려 하거나
	 * 3. 돌이 이미 놓여 있다면
	 돌을 놓을 수 없다.
	*/
	if (!turn_ || !inRange(x,y) || map[y][x]) {
		return NOBODY;
	}
	// 현재 위치에 돌을 놓는다.
	map[y][x] = turn_;
	
	// 턴을 바꾼다.
	turn_ = -turn_;

	/* 위치의 최소 값 갱신 */
	if (min_pos > y * GROUND_SIZE + x) {
		min_pos = y * GROUND_SIZE + x;
	}

	/* 위치의 최대 값 갱신 */
	if (max_pos < y * GROUND_SIZE + x) {
		max_pos = y * GROUND_SIZE + x;
	}

	// 방금 놓은 돌의 상태를 리턴한다.
	return map[y][x];
}

int Omok::IsOmok() const {
	static const int xx[8] = {1,1,0,-1};
	static const int yy[8] = {0,1,1,1};

	int x, y, i, j;

	for(int pos = min_pos; pos <= max_pos; ++pos)
	{
		// 좌표 계산
		i = pos / GROUND_SIZE;
		j = pos % GROUND_SIZE;
		
		// 돌이 놓여져 있으면
		if (map[i][j]) {
			// 4개의 방향에 대해 오목을 검사한다.
			for (int k = 0; k < 4; ++k) {
				
				/* 6번째 돌의 위치 계산 */
				x = j + 5 * xx[k], y = i + +5 * yy[k];

				/* 
				 * 6목이 되는 조건을 검사한다.
				*/
				if (inRange(x, y) && map[y][x] == map[i][j]) {
					/* 6목이 되는 조건 : 6번째 돌이 존재하고, 그 돌이 오목을 구성하는 돌과 같은 종류인 경우 */
					continue;	// 다음 칸으로 넘어간다.
				}

				/*
				 * 오목이 되는 조건을 검사한다.
				*/
				
				bool found = true; // 오목을 못 찾으면 false가 되는 상태 변수
				
				do {
					x -= xx[k], y -= yy[k];
					if (map[y][x] != map[i][j]) {
						found = false;
						break;
					}
				} while (!(x == j && y == i));


				if (!found) {
					continue; // 오목을 못 찾으면, 다음 칸으로 넘어간다.
				}

				return map[i][j]; // 오목을 찾으면, 승자를 리턴한다.
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
	for (int i = 0; i < GROUND_SIZE; ++i) {
		for (int j = 0; j < GROUND_SIZE; ++j) {
			switch (omok.map[i][j]) {
				case BLACK:
					os << "o";
					break;
				case WHITE:
					os << "x";
					break;
				case NOBODY:
					os << ".";
					break;
				default:
					break;
			}
		}
		os << std::endl;
	}
	return os;
}