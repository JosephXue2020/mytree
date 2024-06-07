#pragma once
#include <string>
#include <vector>
#include "inode.h"

template <typename T>
class ITree : virtual public INode<T> {
public:
	virtual ~ITree() = 0;
	virtual bool isRoot() = 0;
	virtual bool isLeaf() = 0;
	virtual std::vector<ITree<T>*> children() = 0;
	virtual ITree<T>* search(std::string id) = 0;
	virtual ITree<T>* insert(ITree<T>*) = 0; // 当前节点插入
	virtual ITree<T>* insert(ITree<T>*, std::string) = 0; // 指定节点插入
	virtual bool remove(std::string id) = 0;
	virtual std::vector<ITree<T>*> traverse() = 0;
	virtual std::vector<ITree<T>*> branch(std::string) = 0;
	virtual std::string str() = 0;
};

template <typename T>
ITree<T>::~ITree() {};