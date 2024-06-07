#pragma once
#include <iostream>
#include "inode.h"

//�������Ļ���node
//ָ��pData����ָ����ڴ��еĶ��󣬷�������ʱ�����
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
