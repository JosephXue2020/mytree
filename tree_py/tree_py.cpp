# include <string>
#include <pybind11/pybind11.h>
#include "../tree/node.h"
#include "../tree/tree.h"

namespace py = pybind11;

template<typename T>
void bind_node(py::module& m, const std::string py_class_name) {
    using Base = Node<T>;
    py::class_<Base>(m, py_class_name.c_str())
        .def(py::init<std::string>())
        ;
}

template<typename T>
void bind_tree(py::module &m, const std::string py_class_name) {
    using Base = Node<T>;
    using Class = Tree<T>;
    py::class_<Class, Base>(m, py_class_name.c_str())
        .def(py::init<std::string, bool>())
       // .def(py::init<std::string, T*, bool>())
        //.def("isRoot", &Class::isRoot)
       // .def("isLeaf", &Class::isLeaf)
       // .def("identifier", &Class::identifier)
      //  .def("str", &Class::str)
       // .def("search", &Class::search)
        ;

}

PYBIND11_MODULE(mytree, m) {
    m.doc() = "pybind11 tree module"; // optional module docstring
    //bind_node<int>(m, "Node");
    bind_tree<int>(m, "Tree");
}