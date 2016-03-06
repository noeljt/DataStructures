#include "utilities.h"
#include "polygons.h"
#include <cassert>

bool Polygon::HasAllEqualSides() const { //simple
	double side_1, side_2;
	for (unsigned int i=0;i<points.size()-1;i++) {
		if (i==points.size()-2) {
			side_1 = DistanceBetween(points[i],points[i+1]);
			side_2 = DistanceBetween(points[i+1],points[0]);
		}
		else {
			side_1 = DistanceBetween(points[i],points[i+1]);
			side_2 = DistanceBetween(points[i+1],points[i+2]);
		}
		if (!EqualSides(side_1,side_2)) return false;
	}
	return true;
}

int Polygon::AdjacentEqualSides() const { //for kite/arrow
	int count = 0;
	double side_1, side_2;
	for (unsigned int i=0;i<points.size();i++) {
		if (i==points.size()-1) {
			side_1 = DistanceBetween(points[i], points[0]);
			side_2 = DistanceBetween(points[0], points[1]);
		}
		else if (i==points.size()-2) {
			side_1 = DistanceBetween(points[i], points[i+1]);
			side_2 = DistanceBetween(points[i+1], points[0]);
		}
		else {
			side_1 = DistanceBetween(points[i], points[i+1]);
			side_2 = DistanceBetween(points[i+1], points[i+2]);
		}
		if (EqualSides(side_1,side_2)) {
		  count++;
		}
	}
	return count;
}

bool Polygon::HasAllEqualAngles() const { //self explanatory
	double angle_1, angle_2;
	for (unsigned int i=0;i<points.size()-1;i++) {
		if (i==points.size()-2) {
			angle_1 = Angle(points[i],points[i+1],points[0]);
			angle_2 = Angle(points[i+1],points[0],points[1]);
		}
		else if (i==points.size()-3) {
			angle_1 = Angle(points[i],points[i+1],points[i+2]);
			angle_2 = Angle(points[i+1],points[i+2],points[0]);
		}
		else {
			angle_1 = Angle(points[i],points[i+1],points[i+2]);
			angle_2 = Angle(points[i+1],points[i+2],points[i+3]);
		}
		if (!EqualAngles(angle_1,angle_2)) return false;
	}
	return true;
}

bool Polygon::EqualBaseAngles() const { //checks for a pair of equal base angles (isosceles)
	double angle_1, angle_2;
	for (unsigned int i=0;i<points.size();i++) {
		if (i==points.size()-1) {
			angle_1 = Angle(points[i],points[0],points[1]);
			angle_2 = Angle(points[0],points[1],points[2]);
		}
		else if (i==points.size()-2) {
			angle_1 = Angle(points[i],points[i+1],points[0]);
			angle_2 = Angle(points[i+1],points[0],points[1]);
		}
		else if (i==points.size()-3) {
			angle_1 = Angle(points[i],points[i+1],points[i+2]);
			angle_2 = Angle(points[i+1],points[i+2],points[0]);
		}
		else {
			angle_1 = Angle(points[i],points[i+1],points[i+2]);
			angle_2 = Angle(points[i+1],points[i+2],points[i+3]);
		}
		if (EqualAngles(angle_1,angle_2)) {
			if (RightAngle(angle_1) and RightAngle(angle_2) and HasAllEqualAngles()) return true;
			if (AcuteAngle(angle_1) and AcuteAngle(angle_2)) return true;
		}
	}
	return false;
}

int Polygon::NumberOfParallelSides() const { //returns number of parallel sides
	int count = 0;
	std::vector<Vector> sides;
	for (unsigned int i=0; i<points.size() ; i++) { //create vector of sides (Vectors)
		if (i==points.size()-1) {
			sides.push_back(Vector(points[i],points[0]));
		}
		else {
			sides.push_back(Vector(points[i],points[i+1]));
		}
	}
	for (unsigned int i=0;i<points.size();i++) { //check other sides with parallel function
		for (unsigned int n=i+1;n<points.size();n++) { //initialize at i+1 to avoid repeats
			if (n==points.size()) {
				if (Parallel(sides[i],sides[0])) {
					count++;
				}
			}
			else {
				if (Parallel(sides[i],sides[n])) {
					count++;
				}
			}
		}
	}
	return count;
}

bool Polygon::HasARightAngle() const {
	double angle;
	for (unsigned int i=0;i<points.size();i++) {
		if (i==points.size()-1) {
			angle = Angle(points[i], points[0], points[1]);
		}
		else if (i==points.size()-2) {
			angle = Angle(points[i], points[i+1], points[0]);	
		}
		else {
			angle = Angle(points[i], points[i+1], points[i+2]);
		}
		if (RightAngle(angle)) return true; //foound a right angle
	}
	return false;
}

bool Polygon::HasAnObtuseAngle() const {
	double angle;
	for (unsigned int i=0;i<points.size();i++) {
		if (i==points.size()-1) {
			angle = Angle(points[i], points[0], points[1]);
		}
		else if (i==points.size()-2) {
			angle = Angle(points[i], points[i+1], points[0]);	
		}
		else {
			angle = Angle(points[i], points[i+1], points[i+2]);
		}
		if (ObtuseAngle(angle)) return true; //found an obtuse angle
	}
	return false;
}

bool Polygon::HasAnAcuteAngle() const {
	double angle;
	for (unsigned int i=0;i<points.size();i++) {
		if (i==points.size()-1) {
			angle = Angle(points[i], points[0], points[1]);
		}
		else if (i==points.size()-2) {
			angle = Angle(points[i], points[i+1], points[0]);	
		}
		else {
			angle = Angle(points[i], points[i+1], points[i+2]);
		}
		if (AcuteAngle(angle)) return true; //found an acute angle
	}
	return false;
}

bool Polygon::HasAReflexAngle() const {
	double angle;
	for (unsigned int i=0;i<points.size();i++) {
		if (i==points.size()-1) {
			angle = Angle(points[i], points[0], points[1]);
		}
		else if (i==points.size()-2) {
			angle = Angle(points[i], points[i+1], points[0]);	}
		else {
			angle = Angle(points[i], points[i+1], points[i+2]);
		}
		if (ReflexAngle(angle)) return true; //found a reflex angle
	}
	return false;
}