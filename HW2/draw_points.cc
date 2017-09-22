#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

struct Point{
	int x, y;
	bool operator==(const Point& p) const{
		return x==p.x && y==p.y;
	}
};

bool exists(const vector<Point> pVec, const Point p){
	int i, size = pVec.size();
	for(i=0; i<size; ++i)
		if(pVec[i]==p)
			return true;
	return false;
}

void draw(const Point p){
	static Point max;
	static vector<Point> pVec;
	
	if(max.x<p.x) max.x = p.x;
	if(max.y<p.y) max.y = p.y;

	pVec.push_back(p);

	Point arg;
	int i, j;
	for(i=0;i<=max.y;++i){
		for(j=0;j<=max.x;++j){
			arg.x = j, arg.y = i;
			cout << (exists(pVec, arg) ? '*' : '.');
		}
		cout << endl;
	}
}

int main(){
	Point p;
	while(true){
		cin >> p.x >> p.y;
		if(p.x<0 || p.y<0) return 0;
		draw(p);
	}
}
