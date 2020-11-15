#include<Python.h>
#include <Windows.h>
#include <structmember.h>
#include "UndirectedWeightedGraph.h"

typedef struct {
    PyObject_HEAD
        UndirectedWeightedGraph graph;
    std::map<double, GraphNode*> finder;
} Graph;

static void Graph_dealloc(Graph* self)
{
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* Graph_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    Graph* self;

    self = (Graph*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->graph = UndirectedWeightedGraph();
        self->finder = std::map<double, GraphNode*>();
    }

    return (PyObject*) (self);
}

static int Graph_init(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    return 0;
}

static PyMemberDef Graph_members[] = {
    {NULL}  /* Sentinel */
};

static PyObject* Graph_addNode(Graph* self, PyObject* args) {
    std::map<std::string, double> map_1;
    map_1["index"] = PyFloat_AsDouble(args);
    GraphNode* new_node = new GraphNode(map_1);
    self->graph.AddNode(new_node);
    self->finder.insert(std::pair<double, GraphNode*>(map_1["index"], new_node));
    return Py_None;
}

static PyObject* Graph_addEdge(Graph* self, PyObject* args) {
    double n1, n2, penalty;
    PyArg_ParseTuple(args, "ddd", &n1, &n2, &penalty);
    GraphNode* node_1 = self->finder.find(n1)->second;
    GraphNode* node_2 = self->finder.find(n2)->second;
    self->graph.AddEdge(new UndirectedWeightedGraphEdge(node_1, node_2, penalty));
    return Py_None;
}

static PyObject* Graph_kruskal(Graph* self) {
    UndirectedWeightedGraph g = self->graph.FindMinimumSpanningTree();
    Graph* new_cp = new Graph();
    new_cp->finder = self->finder;
    new_cp->graph = g;

    return (PyObject*)(new_cp);
}

static PyObject* Graph_getNodes(Graph* self) {
    std::vector<double> values;
    for (GraphNode* node : self->graph.GetNodes()) {
        values.push_back(node->GetData()["index"]);
    }
    PyObject* list_obj = PyList_New(values.size());
    if (!list_obj) throw std::logic_error("Unable to allocate memory for Python list");
    for (size_t i = 0; i < values.size(); i++) {
        PyObject* item = PyFloat_FromDouble(values.at(i));
        if(!item) {
            Py_DECREF(list_obj);
            throw std::logic_error("Unable to allocate memory for Python list");
        }
        PyList_SET_ITEM(list_obj, i, item);
    }
    return list_obj;
}

static PyObject* Graph_getEdges(Graph* self) {
    std::vector<PyObject*> all_tuples;
    for (UndirectedWeightedGraphEdge* edge : self->graph.GetEdges()) {
        PyObject* tuple_new = PyTuple_New(3);
        if (!tuple_new) throw std::logic_error("Unable to allocate memory for Python tuple");
        double index_1 = edge->GetNodes().first->GetData()["index"];
        double index_2 = edge->GetNodes().first->GetData()["index"];
        PyObject* index_1_py = PyFloat_FromDouble(index_1);
        PyObject* index_2_py = PyFloat_FromDouble(index_2);
        PyObject* weight = PyFloat_FromDouble(edge->GetWeight());
        if (!index_1_py || !index_2_py || !weight) {
            Py_DECREF(tuple_new);
            for (PyObject* tuple : all_tuples) {
                Py_DECREF(tuple);
            }
            throw std::logic_error("Unable to allocate memory for Python tuple");
        }
    }

    PyObject* list_obj = PyList_New(all_tuples.size());
    if (!list_obj) throw std::logic_error("Unable to allocate memory for Python list");
    for (size_t i = 0; i < all_tuples.size(); i++) {
        PyObject* item = all_tuples.at(i);
        PyList_SET_ITEM(list_obj, i, item);
    }
    return list_obj;

}

static PyMethodDef Graph_methods[] = {
    {"add_node", (PyCFunction)Graph_addNode, METH_O,
     "Adds a node with a value"
    },
    {"add_edge", (PyCFunction)Graph_addEdge, METH_VARARGS,
     "Adds an edge between the nodes"
    },
    {"find_minimum_spanning_tree", (PyCFunction)Graph_kruskal, METH_NOARGS,
    "Finds the smallest spanning tree"
    },
    {"get_nodes", (PyCFunction)Graph_getNodes, METH_NOARGS,
    "Gets the list of nodes"
    },
    {"get_edges", (PyCFunction)Graph_getEdges, METH_NOARGS,
    "Gets the list of edges"
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject GraphType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "graphmodule.Graph",       /* tp_name */
    sizeof(Graph),             /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)Graph_dealloc, /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE,   /* tp_flags */
    "Undirected Weighted Graph",        /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    Graph_methods,             /* tp_methods */
    Graph_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Graph_init,      /* tp_init */
    0,                         /* tp_alloc */
    Graph_new,                 /* tp_new */
};
static PyModuleDef GraphModule = {
    PyModuleDef_HEAD_INIT,
    "graph",
    "An undirected weighted graph",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC
PyInit_graph(void)
{
    PyObject* m;

    GraphType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&GraphType) < 0)
        return NULL;

    m = PyModule_Create(&GraphModule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&GraphType);
    PyModule_AddObject(m, "Graph", (PyObject*)&GraphType);
    return m;
}