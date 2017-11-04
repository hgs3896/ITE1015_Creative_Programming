#include "draw_shape.h"

Canvas::Canvas(size_t row, size_t col):row(row), col(col) {}
Canvas::~Canvas() {}
int Canvas::AddShape(const Shape &s) {
	if (s.x < 0 || s.y < 0 || s.x >= col || s.y >= row || s.width < 0 || s.height < 0) 
		return ERROR_INVALID_INPUT;

	bool isOutOfRange = false;
	switch (s.type)
	{
		case RECTANGLE:
			// If there exist any even width and height values, return invaild input.
			if (!(s.width * s.height % 2)) return ERROR_INVALID_INPUT;
			// Check if shape s is out of range.
			isOutOfRange = 
				s.x - s.width/2 < 0 ||
				s.x + s.width / 2 >= col ||
				s.y - s.height / 2 < 0 ||
				s.y + s.height / 2 >= row;
			break;
		case TRIANGLE_UP:
			isOutOfRange =
				s.y + (s.height - 1) >= row ||
				s.x - (s.height - 1) < 0 ||
				s.x + (s.height - 1) >= col;
			break;
		case TRIANGLE_DOWN:
			isOutOfRange =
				s.y - (s.height - 1) < 0 ||
				s.x - (s.height - 1) < 0 ||
				s.x + (s.height - 1) >= col;			
			break;
		default:
			break;
	}
	if (isOutOfRange) return ERROR_OUT_OF_CANVAS;

	shapes.push_back(s);
	return shapes.size()-1;
}
void Canvas::DeleteShape(int index) {
	if (index < 0 || index >= shapes.size())
		return;
	shapes.erase(shapes.begin() + index);
}
void Canvas::Draw(std::ostream& os) const{
	int i, j;
	// Dynamic Allocation
	char **map = new char*[row];
	for(i=0;i<row;++i)
		map[i] = new char[col];
	
	// Initialize
	for (i = 0; i < row; ++i)
		for (j = 0; j < col; ++j)
			map[i][j] = '.';
	
	// Draw
	for (const Shape& s : shapes) {
		switch(s.type) {
			case RECTANGLE:
				for (int m = s.height / 2, i = -m; i <= m; ++i)
					for (int n = s.width / 2, j = -n; j <= n; ++j)
						map[s.y + i][s.x + j] = s.brush;
				break;
			case TRIANGLE_UP:
				for (i = 0; i < s.height; ++i)
					for (int n=i, j = -n; j <= n; ++j)
						map[s.y + i][s.x + j] = s.brush;
				break;
			case TRIANGLE_DOWN:
				for (i = 0; i < s.height; ++i)
					for (int n = i, j = -n; j <= n; ++j)
						map[s.y - i][s.x + j] = s.brush;
				break;
		}
	}

	// Print
	os << ' ';
	for (i = 0; i < col; ++i)
		os << i%10;
	os << std::endl;
	for (i = 0; i < row; ++i) {
		os << i%10;
		for (j = 0; j < col; ++j)
			os << map[i][j];
		os << std::endl;
	}

	// Deallocation
	for (i = 0; i < row; ++i)
		delete[] map[i];
	delete[] map;
}
void Canvas::Dump(std::ostream& os) const{
	unsigned int count = 0;
	for (const Shape& s : shapes) {
		os << count++ << " ";
		switch (s.type) {
		case RECTANGLE:
			os << "rect " << s.x << " " << s.y << " " << s.width << " " << s.height;
			break;
		case TRIANGLE_UP:
			os << "tri_up " << s.x << " " << s.y << " " << s.height;
			break;
		case TRIANGLE_DOWN:
			os << "tri_down " << s.x << " " << s.y << " " << s.height;
			break;
		}
		os << " " << s.brush << std::endl;
	}
}