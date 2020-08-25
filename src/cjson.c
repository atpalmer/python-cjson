#include <Python.h>

struct string_builder {
    Py_ssize_t alloc;
    char *curr;
    char value[];
};

static struct string_builder *string_builder_new(Py_ssize_t size) {
    struct string_builder *new = PyMem_Malloc(sizeof(struct string_builder) + size);
    new->alloc = size;
    new->curr = new->value;
    return new;
}

static struct string_builder *string_builder_realloc(struct string_builder *self, Py_ssize_t size) {
    Py_ssize_t currsize = self->curr - self->value;
    Py_ssize_t newalloc = self->alloc;
    while(newalloc < currsize + size)
        newalloc *= 2;
    if(newalloc == self->alloc)
        return self;
    self = PyMem_Realloc(self, sizeof(struct string_builder) + newalloc);
    self->alloc = newalloc;
    self->curr = self->value + currsize;
    return self;
}

static struct string_builder *string_builder_append_char(struct string_builder *self, int c) {
    self = string_builder_realloc(self, 1);
    *self->curr++ = c;
    return self;
}

static PyObject *string_builder_complete(struct string_builder *self) {
    self = string_builder_append_char(self, '\0');
    PyObject *result = PyUnicode_FromString(self->value);
    PyMem_Free(self);
    return result;
}

static PyObject *_cjson_str_dumps(PyObject *str) {
    static const char *ESCAPE_CHARS = "\"\\";
    const char *contents = PyUnicode_AsUTF8(str);
    const char *c = contents;

    struct string_builder *result = string_builder_new(Py_SIZE(str) * 2);
    result = string_builder_append_char(result, '"');
    while(*c) {
        if(strchr(ESCAPE_CHARS, *c))
            result = string_builder_append_char(result, '\\');
        result = string_builder_append_char(result, *c++);
    }
    result = string_builder_append_char(result, '"');
    return string_builder_complete(result);
}

static PyObject *_cjson_int_dumps(PyObject *obj) {
    return PyObject_Str(obj);
}

PyDoc_STRVAR(dumps__doc__, "Accepts obj and return JSON-formatted str");
static PyObject *cjson_dumps(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *obj;
    char *kwlist[] = {"obj", NULL};
    if(!PyArg_ParseTupleAndKeywords(args, kwargs, "O", kwlist, &obj))
        return NULL;

    if(PyUnicode_CheckExact(obj))
        return _cjson_str_dumps(obj);
    if(PyLong_CheckExact(obj))
        return _cjson_int_dumps(obj);

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

