#include <sstream>
#include <string>
#include "point2d.h"

int main() {
	std::string line, cmd;
	
	while (true) {
		std::getline(std::cin, line);
		std::stringstream ss(line);
		ss >> cmd;
		if (cmd == "quit") {
			break;
		}
		else if (cmd == "set") {
			std::string var_name;
			int x, y;
			ss >> var_name >> x >> y;
			if (ss.fail()) {
				continue;
			}
			auto pos = var_name.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
			if (pos != std::string::npos) {
				continue;
			}
			Point p = {x, y};
			p.registerPoint(var_name);
		}
		else if (cmd == "eval") {
			std::string lvar, rvar;
			char op;

			Point l, r;

			ss >> lvar >> op >> rvar;

			if (ss.fail()) {
				break;
			}

			/*
				"eval 수식(lvar) 연산자(+,-,*) 수식(rvar)"
			*/

			if (!l.parseToPoint(lvar) || !r.parseToPoint(rvar)){
				std::cout << "input error" << std::endl;
				continue;
			}

			switch (op) {
			case '+':
				std::cout << l + r << std::endl;
				break;
			case '-':
				std::cout << l - r << std::endl;
				break;
			case '*':
				std::cout << l * r << std::endl;
				break;
			default:
				std::cout << "input error" << std::endl;
				break;
			}
		}
	}
	return 0;
}
