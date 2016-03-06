#include <iostream>
#include <vector>

#include "utilities.h"

#ifndef _polygons_h_
#define _polygons_h_

// POLYGON
class Polygon {
public:
	Polygon(const std::string & name_, const std::vector<Point> & points_) 
	: name(name_), points(points_) {}
	virtual ~Polygon() {} // makes dynamic casting possible

	//ACESSORS
	std::string getName()        const {return name;}
	bool HasAllEqualSides()      const;
	int  AdjacentEqualSides()    const;
	bool EqualBaseAngles()       const;
	int  NumberOfParallelSides() const;
	bool HasAllEqualAngles()     const;
	bool HasARightAngle()        const;
	bool HasAnObtuseAngle()      const;
	bool HasAnAcuteAngle()       const;
	bool HasAReflexAngle()       const;
	bool IsConvex()              const {return (!HasAReflexAngle());}
	bool IsConcave()             const {return HasAReflexAngle();}


protected:
	std::string name;
	std::vector<Point> points;
};

//==================FOUR SIDED============================

// QUADRILATERAL
class Quadrilateral : public Polygon {
public:
	Quadrilateral(const std::string & name_, const std::vector<Point> & points_) 
	: Polygon(name_, points_) {
		if (points.size()!=4) throw 0;
	}
};

// TRAPEZOID
class Trapezoid : virtual public Quadrilateral {
public:
	Trapezoid(const std::string & name_, const std::vector<Point> & points_) 
	: Quadrilateral(name_, points_) {
		if (NumberOfParallelSides()==0) throw 0;
	}
};

// KITE
class Kite : virtual public Quadrilateral {
public:
	Kite(const std::string & name_, const std::vector<Point> & points_) 
	: Quadrilateral(name_, points_) {
		if (AdjacentEqualSides()<2) throw 0;
		if (IsConcave()) throw 0;
	}
};

// ARROW
class Arrow :  public Quadrilateral {
public:
	Arrow(const std::string & name_, const std::vector<Point> & points_)
	: Quadrilateral(name_, points_) {
		if (AdjacentEqualSides()<2) throw 0;
		if (IsConvex()) throw 0;
	}
};

// PARALLELOGRAM
class Parallelogram : virtual public Trapezoid {
public:
	Parallelogram(const std::string & name_, const std::vector<Point> & points_)
	: Quadrilateral(name_, points_), Trapezoid(name_, points_) {
		if (NumberOfParallelSides()!=2) throw 0;
	}
};

// ISOSCELES TRAPEZOID
class IsoscelesTrapezoid : virtual public Trapezoid {
public:
	IsoscelesTrapezoid(const std::string & name_, const std::vector<Point> & points_)
	: Quadrilateral(name_, points_), Trapezoid(name_, points_) {
		if (!EqualBaseAngles()) throw 0;
	}
};

// RHOMBUS
class Rhombus : virtual public Parallelogram, public Kite {
public:
	Rhombus(const std::string & name_, const std::vector<Point> & points_)
	: Quadrilateral(name_, points_), Trapezoid(name_, points_), Parallelogram(name_, points_), 
		Kite(name_, points_) {
		if (!HasAllEqualSides()) throw 0;
	}
};

// RECTANGLE
class Rectangle : virtual public Parallelogram, public IsoscelesTrapezoid {
public:
	Rectangle(const std::string & name_, const std::vector<Point> & points_)
	: Quadrilateral(name_, points_), Trapezoid(name_, points_), Parallelogram(name_, points_), 
		IsoscelesTrapezoid(name_, points_) {
			if (!HasARightAngle()) throw 0;
			if (!HasAllEqualAngles()) throw 0;
		}
};

// SQUARE
class Square : public Rhombus, public Rectangle {
public:
	Square(const std::string & name_, const std::vector<Point> & points_)
	: Quadrilateral(name_, points_), Trapezoid(name_, points_), Parallelogram(name_, points_), 
		Rhombus(name_, points_), Rectangle(name_, points_) {}
};

//========================THREE SIDED===========================================

// TRIANGLE
class Triangle : public Polygon {
public:
	Triangle(const std::string & name_, const std::vector<Point> & points_)
	: Polygon(name_, points_) {
		if (points.size()!=3) throw 0;
	}
};

// ISOSCELES TRIANGLE
class IsoscelesTriangle : virtual public Triangle {
public:
	IsoscelesTriangle(const std::string & name_, const std::vector<Point> & points_)
	: Triangle(name_, points_) {
		if (!EqualBaseAngles()) throw 0;
	}
};

// RIGHT TRIANGLE
class RightTriangle : virtual public Triangle {
public:
	RightTriangle(const std::string & name_, const std::vector<Point> & points_)
	: Triangle(name_, points_) {
		if (!HasARightAngle()) throw 0;
	}
};

// ISOSCELES RIGHT TRIANGLE
class IsoscelesRightTriangle : public IsoscelesTriangle, public RightTriangle {
public:
	IsoscelesRightTriangle(const std::string & name_, const std::vector<Point> & points_)
	: Triangle(name_, points_), IsoscelesTriangle(name_, points_), RightTriangle(name_, points_) {}
};

// OBTUSE TRIANGLE
class ObtuseTriangle : virtual public Triangle {
public:
	ObtuseTriangle(const std::string & name_, const std::vector<Point> & points_)
	: Triangle(name_, points_) {
		if (!HasAnObtuseAngle()) throw 0;
	}
};

// ISOSCELES OBTUSE TRIANGLE
class IsoscelesObtuseTriangle : public IsoscelesTriangle, public ObtuseTriangle {
public:
	IsoscelesObtuseTriangle(const std::string & name_, const std::vector<Point> & points_)
	: Triangle(name_, points_), IsoscelesTriangle(name_, points_), ObtuseTriangle(name_, points_) {}
};

// EQUILATERAL TRIANGLE
class EquilateralTriangle : public IsoscelesTriangle {
public:
	EquilateralTriangle(const std::string & name_, const std::vector<Point> & points_) 
	: Triangle(name_, points_), IsoscelesTriangle(name_, points_) {
		if (!HasAllEqualAngles()) throw 0;
	}
};

//========================================================================================

#endif