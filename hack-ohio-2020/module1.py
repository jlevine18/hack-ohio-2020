from distutils.core import setup, Extension, DEBUG

graph_module = Extension('graph', sources = ['../Graph Modules/Graph_Modules.cpp'])

setup(name = 'graph', version = '1.0',
    description = 'Undirected_Weighted_Graph',
    ext_modules = [graph_module]
    )
