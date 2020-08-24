#include <Python.h>

static PyObject *_cjson_str_dumps(PyObject *str) {
    static const char *ESCAPE_CHARS = "\"\\";
    const char *contents = PyUnicode_AsUTF8(str);

    Py_ssize_t rsize = Py_SIZE(str) * 2;
    char *result = PyMem_Malloc(rsize);

    const char *c = contents;
    char *r = result;

    *r++ = '"';
    while(*c) {
        size_t pos = r - result;
        if(r - result > rsize) {
            rsize *= 2;
            result = PyMem_Realloc(result, rsize);
            r = result + pos;
        }
        if(strchr(ESCAPE_CHARS, *c))
            *r++ = '\\';
        *r++ = *c++;
    }
    *r++ = '"';

    PyObject *result_ob = PyUnicode_FromString(result);
    PyMem_Free(result);
    return result_ob;
}

PyDoc_STRVAR(dumps__doc__, "Accepts obj and return JSON-formatted str");
static PyObject *cjson_dumps(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *obj;
    char *kwlist[] = {"obj", NULL};
    if(!PyArg_ParseTupleAndKeywords(args, kwargs, "O", kwlist, &obj))
        return NULL;

    if(PyUnicode_CheckExact(obj))
        return _cjson_str_dumps(obj);

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

