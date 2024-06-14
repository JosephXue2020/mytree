#pragma once
#include <iostream>

//定义树的基础node

template<typename T>
class Node {
public:
	Node();
	Node(std::string);
	Node(std::string, T);
	virtual ~Node();
	const std::string identifier() const;
	void setId(const std::string);
	const T data();
	void setData(T);
	void setData(T*);
	bool sameId(const Node<T>&);
	bool equal(const Node<T>&);
	std::string str();
protected:
	std::string _id;
	T _data;
};

#include "node.cpp"
