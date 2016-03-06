#ifndef Point_h_
#define Point_h_

class Point {

public:
	//constructor
	Point(int x_, int y_) : p_x(x_), p_y(y_) {}

	//accessors
	int x() const {return p_x;}
	int y() const {return p_y;}

private:
	int p_x,p_y;
};

#endif