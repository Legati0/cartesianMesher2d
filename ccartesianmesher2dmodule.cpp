#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <vector>

#include "cpolyutils2d.hpp"
#include "ccartesianmesher2d.hpp"
#include "definesHeader.hpp"
#include "typeconverter.hpp"

PyObject* mesh(PyObject* self, PyObject* args) {
    PyObject* polyList;
    double minArea;
    // Verify that argument is a list
    if (!PyArg_ParseTuple(args, "O!d", &PyList_Type, &polyList, &minArea)) {
        return NULL;
    }
    // convert input into a polygon
    Polygon poly;
    if (!Polygon_FromPy2DList(polyList, poly))
        return NULL;
    
    List<Rectangle> mesh;
    // mesh
    cMesh(mesh, poly, minArea);

    return Py3DList_FromRectangles(mesh);
}

PyObject* meshMore(PyObject* self, PyObject* args) {
    PyObject* list;
    double minArea;
    // Verify that argument is a list
    if (!PyArg_ParseTuple(args, "O!d", &PyList_Type, &list, &minArea)) {
        return NULL;
    }
    // convert input into a PolyStructure
    PolyStructure polys;
    if (!PolyStructure_FromPyNDList(list, polys))
        return NULL;
    List<Rectangle> mesh;
    // mesh
    cMeshMore(mesh, polys, minArea);

    return Py3DList_FromRectangles(mesh);
}


static PyMethodDef CcartesianmesherMethods[] = {
    {"mesh", mesh, METH_VARARGS,
      "A function that creates a cartesian mesh of a polygon."},
    {"meshMore", meshMore, METH_VARARGS, 
      "A function that creates a cartesian mesh of a polygon structure."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef ccartesianmeshermodule = {
    PyModuleDef_HEAD_INIT,
    "ccartesianMesher2d",   /* name of module */
    "cartesian mesher in 2d", /* module documentation */
    -1,
    CcartesianmesherMethods
};

PyMODINIT_FUNC
PyInit_cartesianMesher2d(void) {
    PyObject* m = PyModule_Create(&ccartesianmeshermodule);
    if (m == NULL) {
        return NULL;
    }
    return m;
}