#include <iostream>
#include <vector>
#include <set>
#include "Point2D.h"
#include "Rectangle.h"

int main()
{
	int hello = 5;
	
	std::cout << "Create and print a rectangle..." << std::endl;
	Point2D p1(0,5);
	Point2D p2(6,10);
	Rectangle r1(p1,p2);
	print_rectangle(r1);
	std::cout << "\nAre the points within the rectangle?" << std::endl;
	Point2D p3(1,6);
	Point2D p4(3,8);
	Point2D p5(2,1);
	Point2D p6(8,3);

	hello = 6;
	
	std::cout << "Should be: true (1)" << std::endl;
	std::cout << r1.is_point_within(p3) << std::endl;
	std::cout << "Should be: true (1)" << std::endl;
	std::cout << r1.is_point_within(p4) << std::endl;
	std::cout << "Should be: false (0)" << std::endl;
	std::cout << r1.is_point_within(p5) << std::endl;
	std::cout << "Should be: false (0)" << std::endl;
	std::cout << r1.is_point_within(p6) << std::endl;
	std::cout << "Can I add the points to the rectangle?" << std::endl;
	std::cout << r1.add_point(p3) << std::endl;
	std::cout << r1.add_point(p4) << std::endl;
	std::cout << r1.add_point(p5) << std::endl;
	std::cout << r1.add_point(p6) << std::endl;
	std::cout << "\nPrint contents..." << std::endl;
	print_rectangle(r1);

	std::cout << "\nCreate and print another rectangle..." << std::endl;
	Point2D p_1(3,3);
	Point2D p_2(9,8);
	Rectangle r2(p_1,p_2);
	print_rectangle(r2);
	Point2D p_3(4,6);
	Point2D p_4(8,4);
	Point2D p_5(1,6);
	
	hello = 0;

	Point2D p_6(8,0);
	std::cout << "\nAre the points within the rectangle?" << std::endl;
	std::cout << "Should be: true (1)" << std::endl;
	std::cout << r2.is_point_within(p_3) << std::endl;
	std::cout << "Should be: true (1)" << std::endl;
	std::cout << r2.is_point_within(p_4) << std::endl;
	std::cout << "Should be: false (0)" << std::endl;
	std::cout << r2.is_point_within(p_5) << std::endl;
	std::cout << "Should be: false (0)" << std::endl;
	std::cout << r2.is_point_within(p_6) << std::endl;
	std::cout << "\nAdd the points to the rectangle?" << std::endl;
	std::cout << r2.add_point(p_3) << std::endl;
	std::cout << r2.add_point(p_4) << std::endl;
	std::cout << r2.add_point(p_5) << std::endl;
	std::cout << r2.add_point(p_6) << std::endl;
	std::cout << "\nPrint contents..." << std::endl;
	print_rectangle(r2);
	std::cout << "\nPoints in both..." << std::endl;
	std::vector<Point2D> both_points = points_in_both(r1,r2);
	for (unsigned int i=0;i<both_points.size();i++)
	{
		std::cout << both_points[i].x() << ',' << both_points[i].y() << '\n';
	}

	hello = 203;

	return 0;
}