#include <Python.h>

static PyObject *cjson_dumps(PyObject *self, PyObject *args, PyObject *kwargs) {
    return NULL;
}

static PyMethodDef module_methods[] = {
    {"dumps", cjson_dumps, METH_VARARGS | METH_KEYWORDS},
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

