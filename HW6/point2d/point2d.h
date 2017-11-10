#include <iostream>
#include <map>
#include <string>

#ifndef _H_POINT2D_
#define _H_POINT2D_

struct Point {
private:
	int x_, y_; // ¸â¹öº¯¼ö
	static std::map<std::string, Point> variables;
public:
	Point();
	Point(const Point& p);
	explicit Point(int c);
	Point(int x, int y);
	Point operator-();
	
	friend bool Point::registerPoint(const std::string& var_name, const Point& p);	
	friend bool parseToPoint(const std::string& arg, Point* p);

	friend Point operator+(const Point& lhs, const Point& rhs);
	friend Point operator-(const Point& lhs, const Point& rhs);
	friend Point operator*(const Point& lhs, const Point& rhs);
	friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

#endif // !_H_POINT2D_