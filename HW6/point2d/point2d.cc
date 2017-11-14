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

bool parseToPoint(const std::string& arg, Point* p) {
	/*
		수식 : [부호][수 또는 변수 명]
	*/
	bool negative = false;
	std::string expr;
	if (arg[0] == '-')
	{
		negative = true;
		expr = arg.substr(1U);
	}
	else if(arg[0] == '+'){
		expr = arg.substr(1U);
	}
	else {
		expr = arg;
	}

	// 숫자가 아닌 것이 있다면,
	if (expr.find_first_not_of("0123456789") != std::string::npos) {
		// 변수명임
		if (!Point::variables.count(expr)) {
			return false;
		}
		*p = negative ? -Point::variables[expr] : Point::variables[expr];
	}
	else {
		// 그냥 숫자임
		int v = stoi(expr);
		p->x_ = p->y_ = negative ? -v : v;
	}
	return true;
}