#include <Python.h>
#include <string>
#include "prefixtrie.h"

typedef struct {
    PyObject_HEAD
    prefixtrie::Node<std::string> *ptrie;
} PrefixTrie_obj;

static PyObject* PrefixTrie_insert(PrefixTrie_obj *self, PyObject *args) {
    char* str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
	return NULL;
    }
    self->ptrie->Insert(str);
    Py_RETURN_NONE;
}

static PyObject* PrefixTrie_walk(PrefixTrie_obj *self) {
    auto elems = self->ptrie->Walk();
    for (auto el : elems)
	std::cout << el << std::endl;
    Py_RETURN_NONE;
}

static PyObject* PrefixTrie_new(PyTypeObject* type, PyObject *args, PyObject *kwds) {
    PrefixTrie_obj *self;
    self = (PrefixTrie_obj *)type->tp_alloc(type, 0);
    self->ptrie = new prefixtrie::Node<std::string>();
    return (PyObject*) self;
}

static int PrefixTrie_init(PrefixTrie_obj *self, PyObject *args, PyObject *kwds) {
    char* str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
	return -1;
    }
    self->ptrie->prefix = str;
    return 0;
}

PyObject* PrefixTrie_ToString(PyObject *self) {
    return PyString_FromString("PrefixTrie");
}

static PyMethodDef  PrefixTrie_methods[] = {
    {"insert", (PyCFunction) PrefixTrie_insert, METH_VARARGS, "Add an element to the PrefixTrie"},
    {"walk", (PyCFunction) PrefixTrie_walk, METH_NOARGS, "Walk the tree"},
    {NULL}  /* Sentinel */
};

static PyTypeObject PrefixTrieType = {
    PyObject_HEAD_INIT(NULL)
    0,                                    /* ob_size is not used anymore, docs don't explain *what* it is */
    "prefixtrie.PrefixTrie",              /* tp_name, string for object */
    sizeof(PrefixTrie_obj),               /* tp_basicsize, how much space to alloc */
    0,                                    /* tp_itemsize */
    0,                                    /* tp_dealloc */
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
    PrefixTrie_ToString,                  /* tp_str */
    0,                                    /* tp_getattro */
    0,                                    /* tp_setattro */
    0,                                    /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                   /* tp_flags */
    "PrefixTrie object",                  /* class docstring */
    0,		                          /* tp_traverse */
    0,		                          /* tp_clear */
    0,		                          /* tp_richcompare */
    0,		                          /* tp_weaklistoffset */
    0,		                          /* tp_iter */
    0,		                          /* tp_iternext */
    PrefixTrie_methods,                   /* tp_methods */
    0,                                    /* tp_members */
    0,                                    /* tp_getset */
    0,                                    /* tp_base */
    0,                                    /* tp_dict */
    0,                                    /* tp_descr_get */
    0,                                    /* tp_descr_set */
    0,                                    /* tp_dictoffset */
    (initproc) PrefixTrie_init,           /* tp_init */
    0,                                    /* tp_alloc */
    (newfunc) PrefixTrie_new,             /* tp_new */
};

static PyMethodDef prefixtrie_funcs[] = {
    // no free functions yet.
    {NULL}
};

PyMODINIT_FUNC initprefixtrie(void) {
    if (PyType_Ready(&PrefixTrieType) < 0)
	return;

    PyObject* m;
    m = Py_InitModule3("prefixtrie", prefixtrie_funcs, "Prefix Trie wrapper module over a C++11 lib.");
    Py_INCREF(&PrefixTrieType);

    PyModule_AddObject(m, "PrefixTrie", (PyObject *) &PrefixTrieType);
}
