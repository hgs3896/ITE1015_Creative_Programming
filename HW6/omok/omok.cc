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
	 * 1. ���� �̹� ����Ǿ��ų�
	 * 2. ���� �ۿ� ���� ������ �ϰų�
	 * 3. ���� �̹� ���� �ִٸ�
	 ���� ���� �� ����.
	*/
	if (!turn_ || !inRange(x,y) || map[y][x]) {
		return NOBODY;
	}
	// ���� ��ġ�� ���� ���´�.
	map[y][x] = turn_;
	
	// ���� �ٲ۴�.
	turn_ = -turn_;

	/* ��ġ�� �ּ� �� ���� */
	if (min_pos > y * GROUND_SIZE + x) {
		min_pos = y * GROUND_SIZE + x;
	}

	/* ��ġ�� �ִ� �� ���� */
	if (max_pos < y * GROUND_SIZE + x) {
		max_pos = y * GROUND_SIZE + x;
	}

	// ��� ���� ���� ���¸� �����Ѵ�.
	return map[y][x];
}

int Omok::IsOmok() const {
	static const int xx[8] = {1,1,0,-1};
	static const int yy[8] = {0,1,1,1};

	int x, y, i, j;

	for(int pos = min_pos; pos <= max_pos; ++pos)
	{
		// ��ǥ ���
		i = pos / GROUND_SIZE;
		j = pos % GROUND_SIZE;
		
		// ���� ������ ������
		if (map[i][j]) {
			// 4���� ���⿡ ���� ������ �˻��Ѵ�.
			for (int k = 0; k < 4; ++k) {
				
				/* 6��° ���� ��ġ ��� */
				x = j + 5 * xx[k], y = i + +5 * yy[k];

				/* 
				 * 6���� �Ǵ� ������ �˻��Ѵ�.
				*/
				if (inRange(x, y) && map[y][x] == map[i][j]) {
					/* 6���� �Ǵ� ���� : 6��° ���� �����ϰ�, �� ���� ������ �����ϴ� ���� ���� ������ ��� */
					continue;	// ���� ĭ���� �Ѿ��.
				}

				/*
				 * ������ �Ǵ� ������ �˻��Ѵ�.
				*/
				
				bool found = true; // ������ �� ã���� false�� �Ǵ� ���� ����
				
				do {
					x -= xx[k], y -= yy[k];
					if (map[y][x] != map[i][j]) {
						found = false;
						break;
					}
				} while (!(x == j && y == i));


				if (!found) {
					continue; // ������ �� ã����, ���� ĭ���� �Ѿ��.
				}

				return map[i][j]; // ������ ã����, ���ڸ� �����Ѵ�.
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