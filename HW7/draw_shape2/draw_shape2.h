#ifndef __H_DRAW_SHAPE_
#define __H_DRAW_SHAPE_

#define DRAW_SHAPE_DEBUG_MODE 0

#include <vector>
#include <iostream>

class Canvas;

class Shape{

public:
	virtual void Draw(Canvas* canvas) const = 0;
	virtual void Dump(std::ostream& os) const = 0;
	virtual ~Shape();
protected:
	int x, y;
	size_t w, h;
	char brush;
};

class Rectangle : public Shape {
public:
	virtual void Draw(Canvas* canvas) const;
	virtual void Dump(std::ostream& os) const;
	friend std::istream& operator>>(std::istream& is, Rectangle& rhs);
};

class UpTriangle : public Shape {
	virtual void Draw(Canvas* canvas) const;
	virtual void Dump(std::ostream& os) const;
	friend std::istream& operator>>(std::istream& is, UpTriangle& rhs);
};

class DownTriangle : public Shape {
	virtual void Draw(Canvas* canvas) const;
	virtual void Dump(std::ostream& os) const;
	friend std::istream& operator>>(std::istream& is, DownTriangle& rhs);
};

class Diamond : public Shape {
	virtual void Draw(Canvas* canvas) const;
	virtual void Dump(std::ostream& os) const;
	friend std::istream& operator>>(std::istream& is, Diamond& rhs);
};

class Canvas {
public:
	Canvas(size_t row, size_t col);
	~Canvas();
	void Resize(size_t w, size_t h);
	bool Draw(int x, int y, char brush);
	void Clear();
	size_t getRow() const { return row; }
	size_t getCol() const { return col; }
private:
	size_t row, col;
	char **map;
	friend std::ostream& operator<<(std::ostream& os, const Canvas& c);
};

#endif // !__H_DRAW_SHAPE_