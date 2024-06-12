#pragma once
#include <string>
#include "node.h"
#include <iostream>

template<typename T>
Node<T>::Node() : pData{nullptr} {
}

template<typename T>
Node<T>::Node(std::string id_) : id{ id_ }, pData{nullptr} {
};

template<typename T>
Node<T>::Node(std::string id_, T data) {
	id = id_;
	pData = new T;
	*pData = data;
};

template<typename T>
Node<T>::Node(std::string id_, T* pData_) {
	id = id_;
	pData = new T;
	*pData = *pData_;
};

template<typename T>
Node<T>::Node(const Node<T>& n) {
	id = n.id;
	pData = new T;
	*pData = *(n.pData);
};

template<typename T>
Node<T>::~Node() {
	//std::cout << "Îö¹¹Node:" << identifier() << std::endl;
	delete pData;
	pData = nullptr;
};

template<typename T>
Node<T>& Node<T>::operator=(const Node<T>& n) {
	id = n.id;
	if (pData != nullptr) {
		delete pData;
	}
	pData = new T;
	*pData = *n.pData;
	return *this;
};

template<typename T>
const std::string Node<T>::identifier() const {
	return id;
};

template<typename T>
void Node<T>::setId(const std::string id_) {
	id = id_;
};

template<typename T>
T& Node<T>::data() {
	return *pData;
};

template<typename T>
void Node<T>::setData(T data) {
	if (pData == nullptr) {
		pData = new T;
	}
	*pData = data;
};

template<typename T>
void Node<T>::setData(T* pData_){
	if (pData == nullptr) {
		pData = new T;
	}
	*pData = *pData_;
};

template<typename T>
bool Node<T>::duplicate(const Node<T>& n) {
	return id == n.id;
};

template<typename T>
bool Node<T>::equal(const Node<T>& n) {
	return *pData == *n.pData;
};

template<typename T>
std::string Node<T>::str() {
	return "Node[" + id + "]";
};
