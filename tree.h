#pragma once
#include <map>
#include <vector>
#include "itree.h"
#include "node.h"

template <typename T>
class Tree : public Node<T>, public ITree<T> {
public:
	Tree(std::string id, bool is_root = false);
	Tree(std::string id, T* pData, bool is_root = false);
	virtual ~Tree();
	bool isRoot();
	bool isLeaf();
	std::vector<ITree<T>*> children();
	ITree<T>* search(std::string id);
	ITree<T>* insert(ITree<T>* subTree);
	ITree<T>* insert(ITree<T>* subTree, std::string targetId);
	bool remove(std::string id);
	std::vector<ITree<T>*> traverse();
	std::vector<ITree<T>*> branch(std::string targetId);
	std::string str();
private:
	bool is_root;
	bool is_leaf;
	std::map<std::string, ITree<T>*> mChildren;
};

#include "tree.cpp"
