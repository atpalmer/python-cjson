#include <Python.h>

PyDoc_STRVAR(dumps__doc__, "Accepts obj and return JSON-formatted str");
static PyObject *cjson_dumps(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *obj;
    char *kwlist[] = {"obj", NULL};
    if(!PyArg_ParseTupleAndKeywords(args, kwargs, "O", kwlist, &obj))
        return NULL;

    PyErr_Format(PyExc_NotImplementedError, "Not implmented for type %s", Py_TYPE(obj)->tp_name);
    return NULL;
}

static PyMethodDef module_methods[] = {
    {"dumps", cjson_dumps, METH_VARARGS | METH_KEYWORDS, dumps__doc__},
    {0},
};

static PyModuleDef module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "cjson",
    .m_size = 0,
    .m_methods = &module_methods,
};

PyMODINIT_FUNC PyInit_cjson(void) {
    PyObject *m = PyModule_Create(&module);
    return m;
}

