#pragma once
#include <iostream>
#include "inode.h"

//定义树的基础node
//指针pData必须指向堆内存中的对象，否则析构时会出错。
template<typename T>
class Node : virtual public INode<T> {
public:
	Node(std::string);
	Node(std::string, T*);
	virtual ~Node();
	const std::string identifier();
	T* data();
	void setData(T*);
	bool equal(INode<T>*);
private:
	std::string id;
	T* pData;
};

#include "node.cpp"
