#pragma once
#include <string>
#include "node.h"
#include <iostream>

template<typename T>
Node<T>::Node() {
};

template<typename T>
Node<T>::Node(std::string id) : _id{ id } {
};

template<typename T>
Node<T>::Node(std::string id, T data) : _id{ id }, _data{data} {
};

template<typename T>
Node<T>::~Node() {
	//std::cout << "Îö¹¹Node:" << identifier() << std::endl;
};

template<typename T>
const std::string Node<T>::identifier() const {
	return _id;
};

template<typename T>
void Node<T>::setId(const std::string id) {
	_id = id;
};

template<typename T>
const T Node<T>::data() {
	return _data;
};

template<typename T>
void Node<T>::setData(T data) {
	_data = data;
};

template<typename T>
void Node<T>::setData(T* pData){
	_data = *pData;
};

template<typename T>
bool Node<T>::sameId(const Node<T>& n) {
	return _id == n._id;
};

template<typename T>
bool Node<T>::equal(const Node<T>& n) {
	return _data == n._data;
};

template<typename T>
std::string Node<T>::str() {
	return "Node[" + _id + "]";
};
