#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "draw_shape2.h"
#if DRAW_SHAPE_DEBUG_MODE
#include <fstream>
#endif

int main() {

#if DRAW_SHAPE_DEBUG_MODE
	std::ifstream in("input.txt");
	std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
	std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
#endif
	std::vector<Shape*> shapes;
	size_t row, col;
	std::cin >> row >> col;
	Canvas canvas(row, col);
	canvas.Clear();
	std::cout << canvas;
	while (true) {
		std::string tok;
		std::cin >> tok;
		if (tok == "add"){
			std::string type;
			std::cin >> type;
			if (type == "rect") {
				Rectangle* shape = new Rectangle();
				std::cin >> *shape;
				shapes.push_back(shape);
			}else if (type == "tri_up") {
				UpTriangle* shape = new UpTriangle();
				std::cin >> *shape;
				shapes.push_back(shape);
			}else if (type == "tri_down") {
				DownTriangle* shape = new DownTriangle();
				std::cin >> *shape;
				shapes.push_back(shape);
			}else if (type == "diamond") {
				Diamond* shape = new Diamond();
				std::cin >> *shape;
				shapes.push_back(shape);
			}

			if (std::cin.fail()) {
				std::cout << "error invailid input" << std::endl;
				continue;
			}
		}
		else if (tok == "delete") {
			int idx;
			std::cin >> idx;
			if (std::cin.fail())
				continue;
			if (idx < shapes.size()) {
				shapes.erase(shapes.begin() + idx);
			}
		}
		else if (tok == "draw") {
			canvas.Clear();
			for (const Shape* s : shapes) {
				s->Draw(&canvas);
			}
			std::cout << canvas;
		}
		else if (tok == "dump") {
			unsigned int count = 0;
			for (const Shape* s : shapes) {
				std::cout << count++ << ' ';
				s->Dump(std::cout);
			}
		}
		else if (tok == "resize") {
			int row, col;
			std::cin >> col >> row;
			canvas.Resize(col, row);
		}
		else if (tok == "quit") {			
			break;
		}
	}

	for (Shape* s : shapes)
		delete s;
	shapes.clear();

#if DRAW_SHAPE_DEBUG_MODE
	std::cin.rdbuf(cinbuf);   //reset to standard input again
#endif
}