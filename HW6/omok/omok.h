#include <iostream>

#ifndef _H_OMOK_
#define _H_OMOK_

class Omok {
public:
	static const int GROUND_SIZE = 19;
	static enum OmokState { BLACK = -1, NOBODY, WHITE };

	Omok();
	int Put(int x, int y);
	int IsOmok() const;
	int Turn() const;
	inline bool inRange(int x, int y) const;
	friend std::ostream& operator<<(std::ostream& os, const Omok& omok);
private:
	int turn_;
	int map[GROUND_SIZE][GROUND_SIZE];
};

#endif // !_H_OMOK_