# include <string>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>`
#include "../tree/node.h"
#include "../tree/tree.h"

namespace py = pybind11;

template<typename T>
void bind_node(py::module& m, const std::string py_class_name) {
    using Class = Node<T>;
    py::class_<Class>(m, py_class_name.c_str())
        .def(py::init<std::string>())
        .def(py::init<std::string,T>())
        .def("identifier", &Class::identifier)
        .def("setId", &Class::setId)
        .def("data", &Class::data)
        .def("setData", &Class::setData)
        .def("duplicate", &Class::duplicate)
        .def("equal", &Class::equal)
        .def("__str__", &Class::str)
        ;
}

template<typename T>
void bind_tree(py::module &m, const std::string py_class_name) {
    using Class = Tree<T>;
    py::class_<Class, Node<T>>(m, py_class_name.c_str())
        .def(py::init<std::string>())
        .def(py::init<std::string, bool>())
        .def(py::init<std::string, T, bool>())
        .def("identifier", &Class::identifier)
        .def("setId", &Class::setId)
        .def("data", &Class::data)
        .def("setData", &Class::setData)
        .def("duplicate", &Class::duplicate)
        .def("equal", &Class::equal)
        .def("__str__", &Class::str)
        .def("isRoot", &Class::isRoot)
        .def("isLeaf", &Class::isLeaf)
        .def("search", &Class::search)
        .def("insert", py::overload_cast<Tree<T>&>(&Class::insert))
        .def("insert", py::overload_cast<Tree<T>&, std::string>(&Class::insert))
        .def("remove", &Class::remove)
        .def("traverse", &Class::traverse)
        .def("branch", &Class::branch)
        ;
}

template<typename T>
void bind_all(py::module& m, const std::string node_name, const std::string tree_name) {
    bind_node<T>(m, node_name);
    bind_tree<T>(m, tree_name);
}

PYBIND11_MODULE(mytree, m) {
    m.doc() = "pybind11 tree module"; // optional module docstring
    //bind_all<int>(m, "Node", "Tree");
    //bind_all<std::string>(m, "Node", "Tree");
    bind_all<py::object>(m, "Node", "Tree");

    //bind_node<int>(m, "Node");
    //bind_node<std::string>(m, "Node");
}