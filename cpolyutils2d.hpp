#ifndef CPOLYUTILS_HPP
#define CPOLYUTILS_HPP

#include <cstddef>
#include <vector>
#include "definesHeader.hpp"

void cGetMinMax(Polygon& poly, double& minX, double& maxX, double& minY, double& maxY);
bool cAreCollin(Point& a, Point& b, Point& c);
double cArea(Polygon& poly, bool absv=true);
bool cIsClockwise(Polygon& poly);
void cToClockwise(Polygon& poly);
void cToAntiClockwise(Polygon& poly);
double cAngle(Point& a, Point& b);
void cRotatePoint(Point& p, Point& o, double angle);
bool cIsPointOnLine(Point& p, Point& l1, Point& l2);
bool cIsPointInPoly(Point& p, Polygon& poly);
int cIsPointInOnOutPoly(Point& p, Polygon& poly);
bool cFindLineIntersection(Point& p1, Point& p2, Point& q1, Point& q2, Point& res);
void cFindIntersections(Polygon& polyA, Polygon& polyB, Polygon& intersections);
int cIsPolyInCutOutPoly(Polygon& polyA, Polygon& polyB);
int cIsPolyInCutOutPoly(Rectangle& polyA, Polygon& polyB);
void cSplitRectInNxM(Rectangle& rect, List<Rectangle>& rects, double minArea=0, long n=2, long m=-1);

#endif /* CPOLYUTILS_HPP */