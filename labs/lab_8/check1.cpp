#include <iostream>

#include "point.h"

//prototype
int paths(const Point & p, int i);

//initial
int paths(const Point & p) {
	if (p.x()==0 and p.y()==0) {
		return 0;
	}
	else {
		if (p.x()==0) {
			Point p_1(p.x(),p.y()-1);
			return paths(p_1,1);
		}
		else if (p.y()==0) {
			Point p_1(p.x()-1,p.y());
			return paths(p_1,1);
		}
		else {
			Point p_1(p.x()-1,p.y());
			Point p_2(p.x(),p.y()-1);
			return (paths(p_1,1)+paths(p_2,1));
		}
	}
}

//
int paths(const Point & p, int i) {
	if (p.x()==0 and p.y()==0) {
		return i;
	}
	else if (p.x()==0) {
		Point n(p.x(),p.y()-1);
		return paths(n,i);
	}
	else if (p.y()==0) {
		Point n(p.x()-1,p.y());
		return paths(n,i);

	}
	else {
		Point n_1(p.x()-1,p.y());
		Point n_2(p.x(),p.y()-1);
		return (paths(n_1,i)+paths(n_2,i));
	}
}

int main(int argc, char* argv[]) {
	int x, y;
	std::cout << "Enter x value: ";
	std::cin >> x;
	std::cout << "Enter y value: ";
	std::cin >> y;
	Point i(x,y);
	std::cout << paths(i);
	return 0;
}