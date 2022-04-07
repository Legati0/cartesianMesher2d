#ifndef TYPECONVERTER_HPP
#define TYPECONVERTER_HPP
#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "definesHeader.hpp"


// Output
// Structure -> PyObject
/**
 * Converts a Polygon to a Py2DList
 * @param poly the polygon that should be converted
 * @return the Py2DList
 */
PyObject* Py2DList_FromPolygon(Polygon& poly);
/**
 * Converts a Rectangle to a Py2DList
 * @param poly the Rectangle that should be converted
 * @return the Py2DList
 */
PyObject* Py2DList_FromRectangle(Rectangle& poly);
/**
 * Converts a List of rectangles to a Py2DList
 * @param rects the List of rectangles that should be converted
 * @return the Py2DList
 */
PyObject* Py3DList_FromRectangles(List<Rectangle>& rects);


// Input
// PyObject -> Structure
/**
 * converts a PyList to a Point
 * @param pypoint the PyList
 * @param point the result Point
 * @return whether or not the converion was successful
 */
bool Point_FromPyList(PyObject* pypoint, Point& point);
/**
 * converts a Py2DList to a Rectangle
 * @param polyList the Py2DList
 * @param poly the result Rectangle
 * @return whether or not the converion was successful
 */
bool Rectangle_FromPy2DList(PyObject* polyList, Rectangle& poly);
/**
 * converts a Py2DList to a Polygon
 * @param polyList the Py2DList
 * @param poly the result Polygon
 * @return whether or not the converion was successful
 */
bool Polygon_FromPy2DList(PyObject* polyList, Polygon& poly);
/**
 * converts a PyNDList to a PolygonStructure
 * @param ndlist the PyNDList
 * @param polys the result PolyStructure
 * @return whether or not the converion was successful
 */
bool PolyStructure_FromPyNDList(PyObject* ndlist, PolyStructure& polys);


#endif /* TYPECONVERTER_HPP */
