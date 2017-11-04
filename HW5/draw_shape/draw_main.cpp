#include <iostream>
#include <sstream>
#include <string>
#include "draw_shape.h"
#if DRAW_SHAPE_DEBUG_MODE
#include <fstream>
#endif

int main() {

#if DRAW_SHAPE_DEBUG_MODE
	std::ifstream in("input.txt");
	std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
	std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
#endif
	Canvas* canvas = nullptr;
	std::string cmd;
	while (true) {
		std::getline(std::cin, cmd);
			std::stringstream ss;
		if (!cmd.find("add")) {
			Shape shape;

			size_t pos_of_cmd;
			if ((pos_of_cmd = cmd.find("rect", 4)) != std::string::npos) {
				shape.type = RECTANGLE;
				ss << cmd.substr(pos_of_cmd + 4);
				ss >> shape.x >> shape.y >> shape.width >> shape.height >> shape.brush;
			}
			else if ((pos_of_cmd = cmd.find("tri_up", 4)) != std::string::npos) {
				shape.type = TRIANGLE_UP;
				ss << cmd.substr(pos_of_cmd + 6);
				ss >> shape.x >> shape.y >> shape.height >> shape.brush;
			}
			else if ((pos_of_cmd = cmd.find("tri_down", 4)) != std::string::npos) {
				shape.type = TRIANGLE_DOWN;
				ss << cmd.substr(pos_of_cmd + 8);
				ss >> shape.x >> shape.y >> shape.height >> shape.brush;
			}
			else {
				std::cout << "error invailid input" << std::endl;
				continue;
			}

			if (ss.fail()) {
				std::cout << "error invailid input" << std::endl;
				continue;
			}

			if (canvas != nullptr) {
				int result = canvas->AddShape(shape);
				if (result == ERROR_OUT_OF_CANVAS) {
					std::cout << "error out of canvas" << std::endl;
					continue;
				}
				else if (result == ERROR_INVALID_INPUT) {
					std::cout << "error invailid input" << std::endl;
					continue;
				}
			}
		}
		else if (!cmd.find("delete")) {
			int index;
			ss << cmd.substr(7);
			ss >> index;
			if (ss.fail())
				continue;
			
			if (canvas != nullptr)
				canvas->DeleteShape(index);
		}
		else if (!cmd.find("draw")) {
			if (canvas != nullptr)
				canvas->Draw(std::cout);
		}
		else if (!cmd.find("dump")) {
			if (canvas != nullptr)
				canvas->Dump(std::cout);
		}
		else if (!cmd.find("quit")) {
			if (canvas != nullptr)
				delete canvas;
			canvas = nullptr;
			break;
		}
		else {
			int row, col;
			ss << cmd;
			ss >> col >> row;
			if (ss.fail() || row <= 0 || col <= 0) continue;	// If the input errors occur, skip.
			
			if (canvas != nullptr)
				delete canvas;

			canvas = new Canvas(row, col);
			canvas->Draw(std::cout);
		}
	}

#if DRAW_SHAPE_DEBUG_MODE
	std::cin.rdbuf(cinbuf);   //reset to standard input again
#endif
}