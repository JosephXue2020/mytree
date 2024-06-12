#pragma once
#include <iostream>

//定义树的基础node

template<typename T>
class Node {
public:
	Node();
	Node(std::string);
	Node(std::string, T);
	Node(std::string, T*);
	Node(const Node<T>&);
	virtual ~Node();
	Node<T>& operator=(const Node<T>&);
	const std::string identifier() const;
	void setId(const std::string);
	T& data();
	void setData(T);
	void setData(T*);
	bool duplicate(const Node<T>&);
	bool equal(const Node<T>&);
	std::string str();
private:
	std::string id;
	T* pData;
};

#include "node.cpp"
