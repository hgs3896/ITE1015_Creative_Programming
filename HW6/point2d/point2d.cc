#include "point2d.h"

Point::Point(): x_(0), y_(0){}
Point::Point(const Point& p) {
	x_ = p.x_, y_ = p.y_;
}
Point::Point(int c) {
	x_ = y_ = c;
}
Point::Point(int x, int y) {
	this->x_ = x, this->y_ = y;
}
Point Point::operator-() {
	return Point(-x_, -y_);
}
Point operator+(const Point& lhs, const Point& rhs) {
	return Point(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
}
Point operator-(const Point& lhs, const Point& rhs) {
	return Point(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_);
}
Point operator*(const Point& lhs, const Point& rhs) {
	return Point(lhs.x_ * rhs.x_, lhs.y_ * rhs.y_);
}
std::ostream& operator<<(std::ostream& os, const Point& p) {
	os << "(" << p.x_ << ", " << p.y_ << ")";
	return os;
}

bool registerPoint(const std::string& var_name, const Point& p) {
	if (Point::variables.count(var_name))
		return false;
	Point::variables[var_name] = p;
	return true;
}

bool parseToPoint(std::string arg, Point* p) {
	if (arg.find_first_not_of("-0123456789") == std::string::npos) {
		*p = Point(stoi(arg));
	}else {
		if (arg[0] == '-') {
			arg = arg.substr(1);

		}
		else {
			if(Point::variables[arg])
		}

	}
	std::cout << "input error" << std::endl;
}