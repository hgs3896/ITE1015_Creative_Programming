#include "minesweeper.h"

Minesweeper::Minesweeper() : map(nullptr), w(0), h(0), tCnt(0), isPlaying(false){}

Minesweeper::~Minesweeper() {
	if (map != nullptr)
		clear2DArray();
}

bool Minesweeper::setMap(size_t _width, size_t _height, const vector<string>& _map) {
	if (_width <= 0 || _height <= 0) return false;
	
	if (map != nullptr)
		clear2DArray();
	initialize(_width, _height);
	allocate2DArray();

	for (int i = 0; i < h; ++i) {
		const char* line = _map[i].c_str();
		for (int j = 0; j < w; ++j)
			if (line[j] == '*')			map[i][j] = 0;
			else if (line[j] == '.')	map[i][j] = 1;
	}
}

bool Minesweeper::toggleMine(int _x, int _y) {
	if (map==nullptr || !inRange(_x, _y) || isVisited(_x, _y)) return false;
	map[_y][_x] = !map[_y][_x];
	return true;
}

bool Minesweeper::setPlay() {
	if (map == nullptr) return false;
	if (isPlaying) {
		tCnt = 0;
		for (int i = 0; i < h; ++i)
			for (int j = 0; j < w; ++j)
				map[i][j] = !isVisited(j, i) ? map[i][j] : -map[i][j];
	}else isPlaying = true;
	return true;
}

bool Minesweeper::touchMap(int _x, int _y) {
	if (!inRange(_x, _y)) return true;
	
	++tCnt;

	if (map[_y][_x] == 0)
		return false;

	if (!isVisited(_x, _y))
		map[_y][_x] = -map[_y][_x];
	else
		--tCnt;
	
	printMap();
	return true;
}

void Minesweeper::printMap() const {
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j)
			if (isVisited(j, i))
				cout << getNearSum(j, i);
			else
				cout << "_";
		cout << endl;
	}
}

void Minesweeper::printMapWithNumbers() const {
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j)
			if (!map[i][j])
				cout << "*";
			else
				cout << getNearSum(j, i);
		cout << endl;
	}
}

char Minesweeper::get(int _x, int _y) const {
	return inRange(_x, _y) ? map[_y][_x] : ' ';
}

inline size_t Minesweeper::width() const {
	return this->w;
}

inline size_t Minesweeper::height() const {
	return this->h;
}

inline bool Minesweeper::inRange(int _x, int _y) const {
	return _x >= 0 && _x < w && _y >= 0 && _y < h;
}

inline bool Minesweeper::isVisited(int _x, int _y) const {
	return map[_y][_x]<0;
}

int Minesweeper::touchCount() const {
	return tCnt;
}

bool Minesweeper::playing() const {
	return isPlaying;
}

int Minesweeper::getNearSum(int x, int y) const{
	int sum = 0;
	for (int k = 0; k < 8; ++k)
		if (inRange(x + xx[k], y + yy[k]))
			sum += !map[y + yy[k]][x + xx[k]];
	return sum;
}

void Minesweeper::allocate2DArray()
{
	map = new int*[h];
	for (int i = 0; i < h; ++i)
		map[i] = new int[w]();
}

void Minesweeper::clear2DArray()
{			
	for(int i=0;i < h;++i)
		delete[] map[i];
	delete[] map;
	map = nullptr;
}

void Minesweeper::initialize(int w, int h) {
	this->w = w;
	this->h = h;
	isPlaying = false;
	tCnt = 0;
}