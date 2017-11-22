#include "draw_shape2.h"

/* Shape */

Shape::~Shape() {

}

/* Rectangle */

void Rectangle::Draw(Canvas* canvas) const {
	for (int i = 0; i < h; ++i)
		for (int j = 0; j < w; ++j)
			canvas->Draw(x + j, y + i, brush);
}

void Rectangle::Dump(std::ostream& os) const {
	os << "rect " << x << ' ' << y << ' ' << w << ' ' << h << ' ' << brush << std::endl;
}

/* UpTriangle */

void UpTriangle::Draw(Canvas* canvas) const {
	for (int i = 0; i < h; ++i)
		for (int n = i, j = -n; j <= n; ++j)
			canvas->Draw(x + j, y + i, brush);
}

void UpTriangle::Dump(std::ostream& os) const {
	os << "tri_up " << x << ' ' << y << ' ' << ' ' << h << ' ' << brush << std::endl;
}

/* DownTriangle */

void DownTriangle::Draw(Canvas* canvas) const {
	for (int i = 0; i < h; ++i)
		for (int n = i, j = -n; j <= n; ++j)
			canvas->Draw(x + j, y - i, brush);
}

void DownTriangle::Dump(std::ostream& os) const {
	os << "tri_down " << x << ' ' << y << ' ' << ' ' << h << ' ' << brush << std::endl;
}

/* Diamond */

void Diamond::Draw(Canvas* canvas) const {
	int i, j;
	for (i = 0; i < h + 1; ++i)
		for (int n = i, j = -n; j <= n; ++j)
			canvas->Draw(x + j, y + i, brush);
	for (i = 0; i < h; ++i)
		for (int n = i, j = -n; j <= n; ++j)
			canvas->Draw(x + j, y + 2 * h - i, brush);
}

void Diamond::Dump(std::ostream& os) const {
	os << "diamond " << x << ' ' << y << ' ' << ' ' << h << ' ' << brush << std::endl;
}

std::istream& operator>>(std::istream& is, Rectangle& rhs) {
	return is >> rhs.x >> rhs.y >> rhs.w >> rhs.h >> rhs.brush;
}

std::istream& operator>>(std::istream& is, UpTriangle& rhs) {
	return is >> rhs.x >> rhs.y >> rhs.h >> rhs.brush;
}

std::istream& operator>>(std::istream& is, DownTriangle& rhs) {
	return is >> rhs.x >> rhs.y >> rhs.h >> rhs.brush;
}

std::istream& operator>>(std::istream& is, Diamond& rhs) {
	return is >> rhs.x >> rhs.y >> rhs.h >> rhs.brush;
}

Canvas::Canvas(size_t row, size_t col):row(row), col(col) {
	int i, j;
	// Dynamic Allocation
	map = new char*[row];
	for (i = 0; i<row; ++i)
		map[i] = new char[col];

	// Initialize
	for (i = 0; i < row; ++i)
		for (j = 0; j < col; ++j)
			map[i][j] = '.';
}

Canvas::~Canvas() {
	// Deallocation
	for (int i = 0; i < row; ++i)
		delete[] map[i];
	delete[] map;
}

void Canvas::Resize(size_t w, size_t h) {
	int i, j;
	
	// Deallocation
	for (int i = 0; i < row; ++i)
		delete[] map[i];
	delete[] map;

	row = h, col = w;

	// Dynamic Allocation
	map = new char*[row];
	for (i = 0; i < h; ++i)
		map[i] = new char[col];

	// Initialize
	for (i = 0; i < row; ++i)
		for (j = 0; j < col; ++j)
			map[i][j] = '.';	
}

bool Canvas::Draw(int x, int y, char brush){
	if (x < 0 || y < 0 || x >= getCol() || y >= getRow()) {
		return false;
	}
	map[y][x]=brush;
	return true;
}

void Canvas::Clear() {
	for (int i = 0; i < row*col; ++i) {
		Draw(i / row, i % row, '.');
	}
}

std::ostream& operator<<(std::ostream& os, const Canvas& c) {
	int i, j;
	// Print
	os << ' ';
	for (i = 0; i < c.getCol(); ++i)
		os << i % 10;
	os << std::endl;
	for (i = 0; i < c.getRow(); ++i) {
		os << i % 10;
		for (j = 0; j < c.getCol(); ++j)
			os << c.map[i][j];
		os << std::endl;
	}
	return os;
}