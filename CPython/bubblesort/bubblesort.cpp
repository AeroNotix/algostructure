#include <Python.h>
#include "bubblesort.h"

static PyObject* bubblesort_sort(PyObject* self, PyObject *args) {
    PyObject* obj;
    PyObject* seq;
    int i, len;

    if (!PyArg_ParseTuple(args, "O", &obj)) {
	return NULL;
    }

    seq = PySequence_Fast(obj,"Expected a sequence");
    if (!seq)
	return NULL;
    len = PySequence_Size(obj);

    std::vector<int> ivec;
    for (i = 0; i < len; ++i) {
	PyObject* item = PySequence_Fast_GET_ITEM(seq, i);
	ivec.push_back(PyInt_AsLong(item));
    }

    PyObject *list = PyList_New(0);

    if (!list)
	return NULL;

    for (auto el : bubblesort(ivec)) {
	PyObject *e = PyInt_FromLong(el);
	if (PyList_Append(list, e) == -1) {
	    Py_DECREF(list);
	    return NULL;
	}
    }
    
    return list;
}

static PyMethodDef bubblesort_funcs[] = {
    {"sort", (PyCFunction) bubblesort_sort, METH_VARARGS, NULL},
    {NULL}
};

PyMODINIT_FUNC initbubblesort(void) {
    Py_InitModule3("bubblesort", bubblesort_funcs, "Bubblesort wrapper over a C++11 lib");
}
