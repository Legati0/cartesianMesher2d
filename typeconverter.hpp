#ifndef TYPECONVERTER_HPP
#define TYPECONVERTER_HPP
#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "definesHeader.hpp"

// Output
// Structure -> PyObject
PyObject* Py2DList_FromPolygon(Polygon& poly);
PyObject* Py2DList_FromRectangle(Rectangle& poly);
PyObject* Py3DList_FromRectangles(List<Rectangle>& rects);

// Input
// PyObject -> Structure
int Point_FromPyList(PyObject* pypoint, Point& point);
int Rectangle_FromPy2DList(PyObject* polyList, Rectangle& poly);
int Polygon_FromPy2DList(PyObject* polyList, Polygon& poly);
int PolyStructure_FromPyNDList(PyObject* ndlist, PolyStructure& polys);

#endif /* TYPECONVERTER_HPP */