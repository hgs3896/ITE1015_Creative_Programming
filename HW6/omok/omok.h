#include <iostream>

#ifndef _H_OMOK_
#define _H_OMOK_

const int GROUND_SIZE = 19;
enum OmokState { BLACK = -1, NOBODY, WHITE };

class Omok {
public:
	Omok();
	~Omok();
	int Put(int x, int y);
	int IsOmok() const;
	int Turn() const;
	inline bool inRange(int x, int y) const;
	friend std::ostream& operator<<(std::ostream& os, const Omok& omok);
private:
	int turn_;
	int** map;
	int min_pos, max_pos;
};

#endif // !_H_OMOK_