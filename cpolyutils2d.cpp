#include "cpolyutils2d.hpp"

#include <algorithm> 
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

void cGetMinMax(Polygon& poly, double& minX, double& maxX, double& minY, double& maxY) {
	minX = poly.at(0).x;
	maxX = poly.at(0).x;
	minY = poly.at(0).y;
	maxY = poly.at(0).y;
	for (auto& point : poly) {
		minX = std::min(minX, point.x);
		maxX = std::max(maxX, point.x);
		minY = std::min(minY, point.y);
		maxY = std::max(maxY, point.y);
	}
}

bool cAreCollin(Point& a, Point& b, Point& c) {
	double val = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
	double deciderVal = 0.000000001;
	return val < deciderVal && val > -deciderVal;
}

double cArea(Polygon& poly, bool absv) {
	double area = 0;
	int j = poly.size() - 1;
	unsigned int i = 0;
	while (i < poly.size()) {
		area += ((poly.at(j).x + poly.at(i).x) * (poly.at(j).y - poly.at(i).y));
		j = i;
		i++;
	}
	if (absv)
		return std::abs(area / 2);
	return area / 2;
}

bool cIsClockwise(Polygon& poly) {
	return cArea(poly, false) > 0;
}

void cToClockwise(Polygon& poly) {
	if (!cIsClockwise(poly))
		std::reverse(poly.begin(), poly.end());
}

void cToAntiClockwise(Polygon& poly) {
	if (cIsClockwise(poly))
		std::reverse(poly.begin(), poly.end());
}

// https://stackoverflow.com/questions/14066933/direct-way-of-computing-clockwise-angle-between-2-vectors
double cAngle(Point& a, Point& b) {
	double dot = a.x * b.x + a.y * b.y;
	double det = a.x * b.y - a.y * b.x;
	double angle = std::atan2(det, dot);
	if (angle > 0)
		return angle;
	else
		return angle + 2 * M_PI; 
}

void cRotatePoint(Point& p, Point& o, double angle) {
	const double s = sin(angle);
	const double c = cos(angle);

	const double x = p.x - o.x;
	const double y = p.y - o.y;

	const double nX = x * c - y * s;
	const double nY = x * s + y * c;

	p.x = nX + o.x;
	p.y = nY + o.y;
}

bool cIsPointOnLine(Point& p, Point& l1, Point& l2) {
	return (p.x >= std::min(l1.x, l2.x)) && (p.x <= std::max(l1.x, l2.x)) &&
			(p.y >= std::min(l1.y, l2.y)) && (p.y <= std::max(l1.y, l2.y)) &&
			cAreCollin(p, l1, l2);
}

bool cIsPointInPoly(Point& p, Polygon& poly) {
	int nvert = poly.size();
	bool c = false;
	for (int i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (
			((poly.at(i).y >= p.y) != (poly.at(j).y >= p.y)) &&
			(p.x <= (poly.at(j).x - poly.at(i).x) * (p.y - poly.at(i).y) / (poly.at(j).y - poly.at(i).y) + poly.at(i).x)
			)
			c = !c;
	}
	return c;
}

int cIsPointInOnOutPoly(Point& p, Polygon& poly) {
	int nvert = poly.size();
	bool c = false;
	for (int i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (cIsPointOnLine(p, poly.at(j), poly.at(i)))
			return 0;
		if (
			((poly.at(i).y >= p.y) != (poly.at(j).y >= p.y)) &&
			(p.x <= (poly.at(j).x - poly.at(i).x) * (p.y - poly.at(i).y) / (poly.at(j).y - poly.at(i).y) + poly.at(i).x)
			)
			c = !c;
	}
	if (c)
		return 1;
	return -1;
}

bool cFindLineIntersection(Point& p1, Point& p2, Point& q1, Point& q2, Point& res) {
	const double s1X = p2.x - p1.x;
	const double s1Y = p2.y - p1.y;
	const double s2X = q2.x - q1.x;
	const double s2Y = q2.y - q1.y;

	const double det = (-s2X * s1Y + s1X * s2Y);
	if (det == 0)
		return false;

	const double s = (-s1Y * (p1.x - q1.x) + s1X * (p1.y - q1.y)) / det;
	const double t = ( s2X * (p1.y - q1.y) - s2Y * (p1.x - q1.x)) / det;

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
		// collision detected
		res.x = p1.x + (t * s1X);
		res.y = p1.y + (t * s1Y);
		return true;
	}
	return false;
}

void cFindIntersections(Polygon& polyA, Polygon& polyB, Polygon& intersections) {
	int anvert = polyA.size();
	int bnvert = polyB.size();
	for (int ai = 0, aj = anvert - 1; ai < anvert; aj = ai++) {
		for (int bi = 0, bj = bnvert - 1; bi < bnvert; bj = bi++) {
			Point p;
			if (cFindLineIntersection(polyA.at(aj), polyA.at(ai),
									  polyB.at(bj), polyB.at(bi), p)) {
				intersections.push_back(p);
			}
		}
	}
}

int cIsPolyInCutOutPoly(Polygon& polyA, Polygon& polyB) {
	// is a in b?
	// 1 inside, -1 outside, 0 cut
	Polygon intersections;
	cFindIntersections(polyA, polyB, intersections);

	// if no intersections, the is no cutting, a has to be in b or the other way around
	if (intersections.empty()) {
		if (cIsPointInPoly(polyA.at(0), polyB))
			return 1;	// is a in B?
		return -1; // if a not in b, it's outside
	}
	
	Polygon nonVertexIntersections;
	for (auto& intersec : intersections) {
		// if intersection is vertex of neither of both polygons
		if (std::find(polyA.begin(), polyA.end(), intersec) == polyA.end() &&
			std::find(polyB.begin(), polyB.end(), intersec) == polyB.end()) {
			nonVertexIntersections.push_back(intersec);
		}
	}

	// if there are intersections that are not vertices, the polygons are cutting each other
	if (!nonVertexIntersections.empty())
		return 0;

	// if there are no intersections left, A and B share at least one edge
	Polygon midPointsA;	// TODO: use midpoints between intersections and points
	int nvert = polyA.size();
	for (int i = 0, j = nvert - 1; i < nvert; j = i++) {
		Point newP;
		newP.x = (polyA.at(j).x + polyA.at(i).x) / 2;
		newP.y = (polyA.at(j).y + polyA.at(i).y) / 2;
		midPointsA.push_back(newP);
	}

	bool inside = false, outside = false;
	// check for each midpoint if they are are inside or outside of b
	for (auto& vert : midPointsA) {
		const int res = cIsPointInOnOutPoly(vert, polyB);
		if (res == 1){
			inside = true;
		}
		else if(res == -1)
			outside = true;
	}
	if (inside && outside){
		return 0;
	}
	else if (inside)
		return 1;
	else if (outside)
		return -1;

	// if neither is inside or outside, it's probably the same poly => inside (TODO get midpoints between vertices and intersections)
	return 1;
}

int cIsPolyInCutOutPoly(Rectangle& polyA, Polygon& polyB) {
	Polygon p;
	for (unsigned int i = 0; i < polyA.size; i++) {
		p.push_back(polyA.points[i]);
	}
	return cIsPolyInCutOutPoly(p, polyB);
}

void cSplitRectInNxM(Rectangle& rect, List<Rectangle>& rects, double minArea, long n, long m) {
	if (m < 0)
		m = n;

	const double width = std::abs(rect.points[0].x - rect.points[2].x);
	const double height = std::abs(rect.points[0].y - rect.points[2].y);
	const double p_width = width / n;
	const double p_height = height / m;
	if (p_width * p_height < minArea)
		return;

	//Point bottomLeft = rect.p1;
	Point bottomLeft = rect.points[0];
	for (unsigned int i = 1; i < rect.size; i++) {
		if (rect.points[i].x < bottomLeft.x && rect.points[i].y < bottomLeft.y)
			bottomLeft = rect.points[i];
	}

	const double x = bottomLeft.x;
	const double y = bottomLeft.y;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			Rectangle poly;
			Point p1 = {x + i 		* p_width, y + j 	   * p_height};
			Point p2 = {x + (i + 1) * p_width, y + j 	   * p_height};
			Point p3 = {x + (i + 1) * p_width, y + (j + 1) * p_height};
			Point p4 = {x + i 		* p_width, y + (j + 1) * p_height};
			poly.points[0] = p1;
			poly.points[1] = p2;
			poly.points[2] = p3;
			poly.points[3] = p4;
			rects.push_back(poly);
		}
	}
}
