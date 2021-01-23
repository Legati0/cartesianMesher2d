#include "typeconverter.hpp"


PyObject* Py2DList_FromPolygon(Polygon poly) {
	PyObject* list = PyList_New(0);
	if (list == NULL)
		return NULL;
	// for every Point in poly create a list for the coord pair and append it to the polygon list
	for(auto& point : poly) {
		PyObject* ls = PyList_New(0);
        if (PyList_Append(ls, PyFloat_FromDouble(point.x)) == -1)
            return NULL;
        if (PyList_Append(ls, PyFloat_FromDouble(point.y)) == -1)
            return NULL;
		if (PyList_Append(list, ls) == -1)
			return NULL;
	}
	return list;
}

PyObject* Py2DList_FromRectangle(Rectangle poly) {
	PyObject* list = PyList_New(0);
	if (list == NULL)
		return NULL;
	// for every Point in poly create a list for the coord pair and append it to the polygon list
	for (unsigned int i = 0; i < poly.size; i++) {
		PyObject* ls = PyList_New(0);
		if (PyList_Append(ls, PyFloat_FromDouble(poly.points[i].x)) == -1)
			return NULL;
		if (PyList_Append(ls, PyFloat_FromDouble(poly.points[i].y)) == -1)
			return NULL;
		if (PyList_Append(list, ls) == -1)
			return NULL;
	}
	return list;
}

PyObject* Py3DList_FromRectangles(std::vector<Rectangle> rects) {
	PyObject* list = PyList_New(0);
	if (list == NULL)
		return NULL;
	// for every rectangle in rects create a 2d list 
	for (auto& rect : rects) {
		PyObject* ls = Py2DList_FromRectangle(rect);
		if (PyList_Append(list, ls) == -1)
			return NULL;
	}

	return list;
}

//#####################################################################################

int Point_FromPyList(PyObject* pypoint, Point* point) {
	// Verify that each pypoint also a list
	if (!PyList_Check(pypoint)) {
		PyErr_SetString(PyExc_TypeError, "must pass in list of list");
		return NULL;
	}
	if (PyList_Size(pypoint) < 2){
		PyErr_SetString(PyExc_TypeError, "coord pair list must have size 2");
		return NULL;
	}
	PyObject* xcoord = PyList_GetItem(pypoint, 0);
	PyObject* ycoord = PyList_GetItem(pypoint, 1);
	// Check that xcoord is a long/double
	if (PyLong_Check(xcoord)) {
		point->x = (double) PyLong_AsLong(xcoord);
	} else if (PyFloat_Check(xcoord)) {
		point->x = PyFloat_AsDouble(xcoord);
	} else {
		PyErr_SetString(PyExc_TypeError, "must pass in list of list of number");
		return NULL;
	}
	// Check that ycoord is a long/double
	if (PyLong_Check(ycoord)) {
		point->y = (double) PyLong_AsLong(ycoord);
	} else if (PyFloat_Check(ycoord)) {
		point->y = PyFloat_AsDouble(ycoord);
	} else {
		PyErr_SetString(PyExc_TypeError, "must pass in list of list of number");
		return NULL;
	}
	return true;
}

int Rectangle_FromPy2DList(PyObject* polyList, Rectangle* poly) {
	if (PyList_Size(polyList) != 4){
		PyErr_SetString(PyExc_TypeError, "must pass in list of size 4");
		return NULL;
	}
	PyObject* pypoint1 = PyList_GetItem(polyList, 0);
	PyObject* pypoint2 = PyList_GetItem(polyList, 1);
	PyObject* pypoint3 = PyList_GetItem(polyList, 2);
	PyObject* pypoint4 = PyList_GetItem(polyList, 3);
	Point p1, p2, p3, p4;
	if (!(Point_FromPyList(pypoint1, &p1) && Point_FromPyList(pypoint2, &p2) && 
			Point_FromPyList(pypoint3, &p3) && Point_FromPyList(pypoint4, &p4)))
		return NULL;

	poly->points[0] = p1;
	poly->points[1] = p2;
	poly->points[2] = p3;
	poly->points[3] = p4;
	return true;
}

int Polygon_FromPy2DList(PyObject* polyList, Polygon* poly) {
	for (int i = 0; i < PyList_Size(polyList); ++i) {
		PyObject* pypoint = PyList_GetItem(polyList, i);
		Point point;
		if (!Point_FromPyList(pypoint, &point))
			return NULL;

		poly->push_back(point);
	}
	return true;
}

int PolyStructure_FromPyNDList(PyObject* ndlist, PolyStructure* polys) {
	for (int i = 0; i < PyList_Size(ndlist); i++) {
		PyObject* fhList = PyList_GetItem(ndlist, i);
		// first element is a polygon that represents a face
		FHObject obj;
		if (!Polygon_FromPy2DList(PyList_GetItem(fhList, 0), &obj.face)) {
			return NULL;
		}
		// if there is another element
		if (PyList_Size(fhList) > 1) {
			// it is a list of holes (each hole is also a polygon)
			PyObject* holesList = PyList_GetItem(fhList, 1);
			for (int j = 0; j < PyList_Size(holesList); j++) {
				Polygon hole;
				if (!Polygon_FromPy2DList(PyList_GetItem(holesList, j), &hole)) {
					return NULL;
				}
				obj.holes.push_back(hole);
			}
		}
		polys->push_back(obj);
	}
	return true;
}