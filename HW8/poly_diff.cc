#include <iostream>
#include <string>
#include <list>
#include <regex>

struct Term {
	int degree;
	int coefficient;
	Term() : degree(0), coefficient(0) {}
};

class Polynomial {
private:
	std::list<Term> poly;
public:
	Polynomial();
	void differentiate();
	int operator()(int rhs) const;
	Polynomial& operator>>(const std::string& expr);
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);
};

Polynomial::Polynomial() {}

void Polynomial::differentiate() {
	for (Term& term : poly) {
		if (term.degree) {
			term.coefficient *= term.degree;
			term.degree -= 1;
		}
		else {
			term.coefficient = 0;
		}
	}
}

int Polynomial::operator()(int rhs) const {
	int sum = 0, value, i;
	for (const auto& term : poly) {
		for (i = 0, value = 1; i < term.degree; ++i) {
			value *= rhs;
		}
		sum += term.coefficient * value;
	}	
	return sum;
}

Polynomial& Polynomial::operator>>(const std::string& expr){
	try{
		std::regex reg(R"(\-)?(?:(\d*)x(?:\^(\d+))?|(\d+))");
		std::smatch m;
	
		std::string txt = expr;

		while (std::regex_search(txt, m, reg)) {

			std::vector<std::string> arr;

			for (auto& sm : m) {
				arr.push_back(static_cast<std::string>(sm));
			}

			bool negative = arr[1][0]=='-';

			Term term;

			if (!arr[4].empty()) {
				term.degree = 0;
				term.coefficient = stoi(arr[2]);
			}
			else {
				term.degree = !arr[3].empty() ? stoi(arr[3]) : 1;
				term.coefficient = !arr[2].empty() ? stoi(arr[2]) : 1;
			}

			if (negative) {
				term.coefficient *= -1;
			}

			poly.push_back(term);

			txt = m.suffix();
		}

		poly.sort([](const Term& a, const Term& b) {return a.degree < b.degree; });
	}catch(const std::regex_error& e){
		std::cout << e.what() << std::endl;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& rhs)
{
	for (const Term& term : rhs.poly) {
		if (term.coefficient) {
			if (term.degree) {
				os << term.coefficient << "x^" << term.degree << "+";
			}
			else {
				os << term.coefficient;
			}
		}
	}
	return os;
}

int main() {
	std::string str;
	int v;
	while (true) {		
		std::cin >> str;
		if (str == "quit") {
			break;
		}
		std::cin >> v;
		Polynomial poly;
		poly >> str;
		poly.differentiate();
		std::cout << poly(v) << std::endl;
	}
}
