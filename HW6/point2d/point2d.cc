#include "point2d.h"

std::map<std::string, Point> Point::variables;

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

bool Point::registerPoint(const std::string& var_name) const {
	if (variables.count(var_name))
		return false;
	variables[var_name] = *this;
	return true;
}

bool Point::parseToPoint(const std::string& arg) {
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

	if (expr.find_first_not_of("0123456789") != std::string::npos) {
		if (!variables.count(expr)) {
			return false;
		}
		*this = negative ? -variables[expr] : variables[expr];
	}
	else {
		int v = stoi(expr);
		this->x_ = this->y_ = negative ? -v : v;
	}
	return true;
}
