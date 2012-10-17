#include <Python.h>
#include <iostream>
#include "binarytree.h"
#include <vector>

typedef struct {
    PyObject_HEAD
    binarytree::BinaryTree<PyObject*> btree;
} BinaryTree_obj;

static void BinaryTree_dealloc(BinaryTree_obj *self) {
    for (auto el : self->btree.Walk())
	Py_XDECREF(el);
    self->btree.~BinaryTree();
}

static PyObject* BinaryTree_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {

    BinaryTree_obj *self;

    binarytree::BinaryTree<PyObject*> tmp = binarytree::BinaryTree<PyObject*>();
    self->btree = tmp;
    self = (BinaryTree_obj*) type->tp_alloc(type, 0);
    if (!self)
	return NULL;
    return (PyObject*) self;
}

PyObject* BinaryTree_ToString(PyObject *self) {
    return PyString_FromString("BinaryTree");
}

static PyObject* BinaryTree_add(BinaryTree_obj *self, PyObject *args) {
    PyObject* obj;
    if (!PyArg_ParseTuple(args, "O", &obj)) {
	return NULL;
    }
    self->btree.Add(obj);
    Py_RETURN_NONE;
}

static PyObject* BinaryTree_walk(BinaryTree_obj *self) {
    auto sortedItems = self->btree.Walk();
    PyObject *list = PyList_New(0);
    for (auto el : sortedItems) {
	if (PyList_Append(list, el) == -1) {
	    return NULL;
	}
    }
    return list;
}

static PyMethodDef  BinaryTree_methods[] = {
    {"add", (PyCFunction) BinaryTree_add, METH_VARARGS, "Add an element to the BinaryTree"},
    {"walk", (PyCFunction) BinaryTree_walk, METH_NOARGS, "Walk the tree and return a list"},
    {NULL}  /* Sentinel */
};

static PyTypeObject BinaryTreeType = {
    PyObject_HEAD_INIT(NULL)
    0,                                    /* ob_size is not used anymore, docs don't explain *what* it is */
    "binarytree.BinaryTree",              /* tp_name, string for object */
    sizeof(BinaryTree_obj),               /* tp_basicsize, how much space to alloc */
    0,                                    /* tp_itemsize */
    (destructor) BinaryTree_dealloc,      /* tp_dealloc */
    0,                                    /* tp_print */
    0,                                    /* tp_getattr */
    0,                                    /* tp_setattr */
    0,                                    /* tp_compare */
    0,                                    /* tp_repr */
    0,                                    /* tp_as_number */
    0,                                    /* tp_as_sequence */
    0,                                    /* tp_as_mapping */
    0,                                    /* tp_hash */
    0,                                    /* tp_call */
    BinaryTree_ToString,                  /* tp_str */
    0,                                    /* tp_getattro */
    0,                                    /* tp_setattro */
    0,                                    /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                   /* tp_flags */
    "BinaryTree object",                  /* class docstring */
    0,		                          /* tp_traverse */
    0,		                          /* tp_clear */
    0,		                          /* tp_richcompare */
    0,		                          /* tp_weaklistoffset */
    0,		                          /* tp_iter */
    0,		                          /* tp_iternext */
    BinaryTree_methods,                   /* tp_methods */
    0,                                    /* tp_members */
    0,                                    /* tp_getset */
    0,                                    /* tp_base */
    0,                                    /* tp_dict */
    0,                                    /* tp_descr_get */
    0,                                    /* tp_descr_set */
    0,                                    /* tp_dictoffset */
    0,                                    /* tp_init */
    0,                                    /* tp_alloc */
    BinaryTree_new,                       /* tp_new */
};

static PyMethodDef binarytree_funcs[] = {
    // no free functions yet.
    {NULL}
};

PyMODINIT_FUNC initbinarytree(void) {
    BinaryTreeType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&BinaryTreeType) < 0)
	return;

    PyObject* m;
    m = Py_InitModule3("binarytree", binarytree_funcs, "Binary Tree wrapper module over a C++11 lib.");
    Py_INCREF(&BinaryTreeType);

    PyModule_AddObject(m, "BinaryTree", (PyObject *) &BinaryTreeType);
}
