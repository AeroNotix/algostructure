#include <Python.h>
#include <iostream>
#include "binarytree.h"

static PyObject* binarytree_newtree(PyObject* self, PyObject *args) {
	binarytree::BinaryTree<PyObject*> *n = new binarytree::BinaryTree<PyObject*>();
	std::cout << "Hello, lulz" << std::endl;
    Py_RETURN_NONE;
}

static PyMethodDef binarytree_funcs[] = {
    {"tree", (PyCFunction) binarytree_newtree, METH_VARARGS, NULL},
    {NULL}
};

PyMODINIT_FUNC initbinarytree(void) {
    Py_InitModule3("binarytree", binarytree_funcs, "Binary Tree wrapper module over a C++11 lib.");
}
