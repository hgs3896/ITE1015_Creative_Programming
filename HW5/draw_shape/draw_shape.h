#ifndef __H_DRAW_SHAPE_
#define __H_DRAW_SHAPE_

#define DRAW_SHAPE_DEBUG_MODE 0

#include <vector>
#include <iostream>
enum { RECTANGLE, TRIANGLE_UP, TRIANGLE_DOWN };
enum { ERROR_OUT_OF_CANVAS = -1, ERROR_INVALID_INPUT = -2 }; 
struct Shape{
	int type;
	int x, y;
	int width, height;
	char brush;
};
class Canvas {
public:
	Canvas(size_t row, size_t col);
	~Canvas();
	int AddShape(const Shape &s);
	void DeleteShape(int index);
	void Draw(std::ostream& os) const;
	void Dump(std::ostream& os) const;
private:
	size_t row, col;
	std::vector<Shape> shapes;
};

#endif // !__H_DRAW_SHAPE_