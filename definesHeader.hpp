#ifndef DEFINESHEADER_HPP
#define DEFINESHEADER_HPP

#include <vector>


#define Polygon std::vector<Point>
#define PolyStructure std::vector<FHObject>

struct Point {
	double x;
	double y;
	Point() {}
	Point(double _x, double _y) : x(_x), y(_y) {}
	bool operator==(const Point other)
	{
	    return x == other.x && y == other.y;
	}
};

struct Rectangle {
	Point points[4];
	unsigned int size = 4;
	bool operator==(const Rectangle other)
	{
	    for (unsigned int i = 0; i < size; i++)
	    	if (!(points[i] == other.points[i]))
	    		return false;
	    return true;
	}
};

struct FHObject {
	Polygon face;
	std::vector<Polygon> holes;
};

#endif /* DEFINESHEADER_HPP */