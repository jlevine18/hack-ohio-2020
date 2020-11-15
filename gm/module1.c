#include <Python.h> 

/*
 * Implements an example function.
 */
PyDoc_STRVAR(graph_modules_example_doc, "example(obj, number)\
\
Example function");

PyObject *graph_modules_example(PyObject *self, PyObject *args, PyObject *kwargs) {
    /* Shared references that do not need Py_DECREF before returning. */
    PyObject *obj = NULL;
    int number = 0;

    /* Parse positional and keyword arguments */
    static char* keywords[] = { "obj", "number", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi", keywords, &obj, &number)) {
        return NULL;
    }

    /* Function implementation starts here */

    if (number < 0) {
        PyErr_SetObject(PyExc_ValueError, obj);
        return NULL;    /* return NULL indicates error */
    }

    Py_RETURN_NONE;
}

/*
 * List of functions to add to graph_modules in exec_graph_modules().
 */
static PyMethodDef graph_modules_functions[] = {
    { "example", (PyCFunction)graph_modules_example, METH_VARARGS | METH_KEYWORDS, graph_modules_example_doc },
    { NULL, NULL, 0, NULL } /* marks end of array */
};

/*
 * Initialize graph_modules. May be called multiple times, so avoid
 * using static state.
 */
int exec_graph_modules(PyObject *module) {
    PyModule_AddFunctions(module, graph_modules_functions);

    PyModule_AddStringConstant(module, "__author__", "jlevi");
    PyModule_AddStringConstant(module, "__version__", "1.0.0");
    PyModule_AddIntConstant(module, "year", 2020);

    return 0; /* success */
}

/*
 * Documentation for graph_modules.
 */
PyDoc_STRVAR(graph_modules_doc, "The graph_modules module");


static PyModuleDef_Slot graph_modules_slots[] = {
    { Py_mod_exec, exec_graph_modules },
    { 0, NULL }
};

static PyModuleDef graph_modules_def = {
    PyModuleDef_HEAD_INIT,
    "graph_modules",
    graph_modules_doc,
    0,              /* m_size */
    NULL,           /* m_methods */
    graph_modules_slots,
    NULL,           /* m_traverse */
    NULL,           /* m_clear */
    NULL,           /* m_free */
};

PyMODINIT_FUNC PyInit_graph_modules() {
    return PyModuleDef_Init(&graph_modules_def);
}
