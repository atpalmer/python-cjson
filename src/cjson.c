#include <Python.h>

static PyModuleDef module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "cjson",
    .m_size = 0,
};

PyMODINIT_FUNC PyInit_cjson(void) {
    PyObject *m = PyModule_Create(&module);
    return m;
}

