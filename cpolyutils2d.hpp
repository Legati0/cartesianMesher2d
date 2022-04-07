#ifndef CPOLYUTILS_HPP
#define CPOLYUTILS_HPP

#include <cstddef>
#include <vector>
#include "definesHeader.hpp"


/**
 * calculate min/max x/y values of a Polygon
 * @param poly the source Polygon
 * @param minX min x return value
 * @param maxX max x return value
 * @param minY min y return value
 * @param maxY max y return value
 */
void cGetMinMax(const Polygon& poly, double& minX, double& maxX, double& minY, double& maxY);
/**
 * calculate min/max x/y values of a Polygon
 * @param poly the source Polygon
 * @param min return Point that holds minimum x,y
 * @param max return Point that holds maximum x,y
 */
void cGetMinMax(const Polygon& poly, Point& min, Point& max);
/**
 * calculates if three points are colinear
 * @param a Point 1
 * @param b Point 2
 * @param c Point 3
 * @return whether or not the tree points are colinear
 */
bool cAreCollin(const Point& a, const Point& b, const Point& c);
/**
 * calculates area of a Polygon
 * @param poly Polygon
 * @param absv whether area should be returned as absolute value
 * @return area
 */
double cArea(const Polygon& poly, bool absv=true);
/**
 * calculates whether a Polygon is clockwise
 * @param poly Polygon
 * @return whether the Polygon is clockwise
 */
bool cIsClockwise(const Polygon& poly);
/**
 * turns a Polygon into clockwise orientation
 * @param poly Polygon that will be oriented to clockwise
 */
void cToClockwise(Polygon& poly);
/**
 * turns a Polygon into anticlockwise orientation
 * @param poly Polygon that will be oriented to anticlockwise
 */
void cToAntiClockwise(Polygon& poly);
/**
 * calculates the angle between two vectors
 * points are used as vector
 * @param a Vector 1
 * @param b Vector 2
 * @return the angle
 */
double cAngle(const Point& a, const Point& b);
/**
 * rotates Point p around Point b with angle
 * @param p Point that gets rotated
 * @param o origin Point
 * @param the angle
 */
void cRotatePoint(Point& p, const Point& o, double angle);
/**
 * calculates whether a point is on the line between two other Points
 * @param p Point
 * @param l1 End of Line on side 1
 * @param l2 End of Line on side 2
 * @return whether or not the point is on the line
 */
bool cIsPointOnLine(const Point& p, const Point& l1, const Point& l2);
/**
 * calculates whether the Point is in the Poly
 * @param p Point
 * @param poly Polygon
 * @return whether or not the Point is in the Polygon
 */
bool cIsPointInPoly(const Point& p, const Polygon& poly);
/**
 * calculates whether the Point is/out of/on the Poly
 * @param p Point
 * @param poly Polygon
 * @return 1, if Point is in, -1, if Point is out, 0 if Point is on the Polygon
 */
int cIsPointInOnOutPoly(const Point& p, const Polygon& poly);
/**
 * calculates the intersection of two lines
 * @param p1 Line 1 Point 1
 * @param p2 Line 1 Point 2
 * @param q1 Line 2 Point 1
 * @param q2 Line 2 Point 2
 * @param res intersection point (if there is one)
 * @return true if there is an intersection, false if not
 */
bool cFindLineIntersection(const Point& p1, const Point& p2, const Point& q1, const Point& q2, Point& res);
/**
 * calculates the intersections between two Polygons
 * @param polyA Polygon 1
 * @param polyB Polygon 2
 * @param intersections List of intersections of the two polygons
 */
void cFindIntersections(const Polygon& polyA, const Polygon& polyB, Polygon& intersections);
/**
 * calculates if Polygon 1 is in/out or cutting Polygon 2
 * @param polyA Polygon 1
 * @param polyB Polygon 2
 * @return 0, if cut, 1 if in, -1 if out
 */
int cIsPolyInCutOutPoly(const Polygon& polyA, const Polygon& polyB);
/**
 * calculates if Rectangle is in/out or cutting Polygon
 * @param polyA Rectangle
 * @param polyB Polygon
 * @return 0, if cut, 1 if in, -1 if out
 */
int cIsPolyInCutOutPoly(const Rectangle& polyA, const Polygon& polyB);
/**
 * splits a Rectangle into n*m Rectangles
 * @param rect Rectangle to split
 * @param rects return List
 * @param minArea minimum area of rectangles, if split rects would be smaller than minArea, empty list returned
 * @param n split into n in horizontal direction
 * @param m=n split into m in vertical direction
 */
void cSplitRectInNxM(const Rectangle& rect, List<Rectangle>& rects, double minArea=0, long n=2, long m=-1);


#endif /* CPOLYUTILS_HPP */
