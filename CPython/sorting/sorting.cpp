#include <Python.h>
#include "bubblesort.h"
#include "quicksort.h"
#include "selection.h"

static PyObject* quicksort_sort(PyObject* self, PyObject *args) {
    PyObject* obj;
    PyObject* seq;
    int i, len;

    if (!PyArg_ParseTuple(args, "O", &obj)) {
	return NULL;
    }

    seq = PySequence_Fast(obj,"Expected a sequence");
    len = PySequence_Size(obj);

    std::vector<int> ivec;
    for (i = 0; i < len; ++i) {
	PyObject* item = PySequence_Fast_GET_ITEM(seq, i);
	ivec.push_back(PyInt_AsLong(item));
    }

    PyObject *list = PyList_New(0);

    if (!list)
	return NULL;

    for (auto el : quicksort(ivec)) {
	PyObject *e = PyInt_FromLong(el);
	if (PyList_Append(list, e) == -1) {
	    Py_DECREF(list);
	    return NULL;
	}
    }
    
    Py_DECREF(obj);
    Py_DECREF(seq);

    return list;
}

static PyObject* bubble_sort(PyObject* self, PyObject *args) {
    PyObject* obj;
    PyObject* seq;
    int i, len;

    if (!PyArg_ParseTuple(args, "O", &obj)) {
	return NULL;
    }

    seq = PySequence_Fast(obj,"Expected a sequence");
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
    
    Py_DECREF(obj);
    Py_DECREF(seq);

    return list;
}

static PyObject* select_sort(PyObject* self, PyObject *args) {
    PyObject* obj;
    PyObject* seq;
    int i, len;

    if (!PyArg_ParseTuple(args, "O", &obj)) {
	return NULL;
    }

    seq = PySequence_Fast(obj,"Expected a sequence");
    len = PySequence_Size(obj);

    std::vector<int> ivec;
    for (i = 0; i < len; ++i) {
	PyObject* item = PySequence_Fast_GET_ITEM(seq, i);
	ivec.push_back(PyInt_AsLong(item));
    }

    PyObject *list = PyList_New(0);

    if (!list)
	return NULL;

    for (auto el : selectionsort(ivec)) {
	PyObject *e = PyInt_FromLong(el);
	if (PyList_Append(list, e) == -1) {
	    Py_DECREF(list);
	    return NULL;
	}
    }
    
    Py_DECREF(obj);
    Py_DECREF(seq);

    return list;
}

static PyMethodDef sorting_funcs[] = {
    {"select", (PyCFunction) select_sort, METH_VARARGS, "Selection sort"},
    {"qsort", (PyCFunction) quicksort_sort, METH_VARARGS, "Quicksort"},
    {"bubble", (PyCFunction) bubble_sort, METH_VARARGS, "Bubblesort"},
    {NULL}
};

PyMODINIT_FUNC initsorting(void) {
    Py_InitModule3("sorting", sorting_funcs, "C++11 implementations of various sorting algorithms");
}
