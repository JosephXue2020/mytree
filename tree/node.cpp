#pragma once
#include <string>
#include "node.h"
#include <iostream>

template<typename T>
Node<T>::Node(std::string id) {
	this->id = id;
};

template<typename T>
Node<T>::Node(std::string id, T* pData) {
	this->id = id;
	this->pData = pData;
};

template<typename T>
Node<T>::~Node() {
	delete pData;
};

template<typename T>
const std::string Node<T>::identifier() {
	return id;
};

template<typename T>
T* Node<T>::data() {
	return pData;
};

template<typename T>
void Node<T>::setData(T* pData){
	this->pData = pData;
};

template<typename T>
bool Node<T>::equal(INode<T>* n) {
	return identifier() == n->identifier();
};

