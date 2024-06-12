#pragma once
#include <map>
#include <vector>
#include "node.h"


template <typename T>
class Tree : public Node<T> {
public:
	Tree();
	Tree(std::string);
	Tree(std::string, bool);
	Tree(std::string, T, bool);
	Tree(std::string, T*, bool);
	Tree(Tree<T>&);
	virtual ~Tree();
	Tree<T>& operator=(const Tree<T>&);
	bool isRoot();
	bool isLeaf();
	std::vector<Tree<T>*> children();
	Tree<T>* search(std::string);
	Tree<T>* insert(Tree<T>&);
	Tree<T>* insert(Tree<T>&, std::string);
	bool remove(std::string);
	std::vector<Tree<T>*> traverse();
	std::vector<Tree<T>*> branch(std::string);
	std::string str();
private:
	bool is_root;
	bool is_leaf;
	std::map<std::string, Tree<T>*> mChildren;
};

#include "tree.cpp"
