#ifndef __HDR__MINE_SWEEPER__
#define __HDR__MINE_SWEEPER__

#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class Minesweeper
{
public:
	////////// 4-3-1 (7 score) //////////
	Minesweeper();
	~Minesweeper();

	// return false when input is incorrect
	bool setMap(size_t _width, size_t _height, const vector<string>& _map);
	bool toggleMine(int _x, int _y);

	////////// 4-3-2 (3 score) //////////
	bool setPlay(); // return false when map is not set
	bool touchMap(int _x, int _y); // return true when dead
	
	// Printing Functions
	void printMap() const;
	void printMapWithNumbers() const;

	// State Functions
	char get(int _x, int _y) const; // return ' ' if input is illegal
	inline size_t width() const;
	inline size_t height() const;
	inline bool inRange(int _x, int _y) const;
	inline bool isVisited(int _x, int _y) const;	
	int touchCount() const;
	bool playing() const;
private:
	// add private member variables and functions if it is needed.
	int **map;
	size_t w, h;
	int tCnt;
	bool isPlaying;

	const int xx[8] = {1,0,-1,0,1,1,-1,-1};
	const int yy[8] = {0,1,0,-1,-1,1,1,-1};

	int getNearSum(int x, int y) const;

	// Allocation and Initializing Funcitons
	void allocate2DArray();
	void clear2DArray();
	void initialize(int w, int h);
};
#endif // !__HDR__MINE_SWEEPER__