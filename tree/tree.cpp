#pragma once
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include "itree.h"
#include "node.h"
#include "tree.h"
#include <iostream>


template <typename T>
Tree<T>::Tree(std::string id, bool is_root) :
	Node<T>(id) {
	this->is_root = is_root;
	this->is_leaf = true;
};

template <typename T>
Tree<T>::Tree(std::string id, T* pData, bool is_root) :
	Node<T>(id, pData) {
	this->is_root = is_root;
	this->is_leaf = true;
};

template <typename T>
Tree<T>::~Tree() {
	std::vector<ITree<T>*> kids = children();
	if (kids.size() > 0) {
		for (auto it = kids.begin(); it != kids.end(); it++) {
			delete *it;
		}
	};
}

template <typename T>
bool Tree<T>::isRoot() {
	return is_root;
};

template <typename T>
bool Tree<T>::isLeaf() {
	return is_leaf;
};

template <typename T>
std::vector<ITree<T>*> Tree<T>::children() {
	std::vector<ITree<T>*> buf;
	typename std::map<std::string,ITree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		buf.push_back(it->second);
	}
	return buf;
};

// 递归查找
template <typename T>
ITree<T>* Tree<T>::search(std::string id) {
	if (id == this->identifier()) {
		return this;
	}

	typename std::map<std::string, ITree<T>*>::iterator foundPair = mChildren.find(id);
	if (foundPair != mChildren.end()) {
		return foundPair->second;
	}

	typename std::map<std::string, ITree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		ITree<T>* subtree = it->second;
		ITree<T>* found = subtree->search(id);
		if (found != NULL) {
			return found;
		}
	}

	return NULL;
};

template <typename T>
ITree<T>* Tree<T>::insert(ITree<T>* pSubtree) {
	std::string subid = pSubtree->identifier();
	typename std::map<std::string, ITree<T>*>::iterator pairFound = mChildren.find(subid);
	if (pairFound != mChildren.end()) {
		/*std::invalid_argument e("id exists");
		throw e;*/
		return NULL;
	}

	mChildren[subid] = pSubtree;
	if (isLeaf()) {
		is_leaf = false;
	}
	return pSubtree;
};

template <typename T>
ITree<T>* Tree<T>::insert(ITree<T>* pSubtree, std::string targetId) {
	ITree<T>* target = this->search(targetId);
	if (target == NULL) {
		return NULL;
	}
	
	return target->insert(pSubtree);
};

// 不能remove自身
template <typename T>
bool Tree<T>::remove(std::string id) {
	// 子节点中寻找
	if (this->mChildren.count(id) > 0) {
		ITree<T>* pSubtree = this->mChildren[id];
		delete pSubtree;
		this->mChildren.erase(id);
		return true;
	}

	// 子节点中没有找到
	typename std::map<std::string, ITree<T>*>::iterator it;
	for (it = this->mChildren.begin(); it != this->mChildren.end(); it++) {
		ITree<T>* pSubtree = it->second;
		int count = pSubtree->remove(id);
		if (count > 0) {
			return true;
		}
	}

	return false;
};

template <typename T>
std::string Tree<T>::str() {
	std::string s = this->identifier();

	if (isLeaf()) {
		s += "(leaf)";
	}

	s += ":[";

	std::vector<ITree<T>*> kids = children();
	for (std::size_t i = 0; i < kids.size(); i++) {
		ITree<T>* kid = kids[i];
		s += kid->identifier();
		if (kid->isLeaf()) {
			s += "(leaf)";
		};
		if (i < kids.size() - 1) {
			s += ",";
		};
	}

	s += "]";
	return s;
};

//dfs先序遍历
template <typename T>
std::vector<ITree<T>*> Tree<T>::traverse() {
	std::vector<ITree<T>*> buf{this};
	typename std::map<std::string, ITree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		std::vector<ITree<T>*> temp = (it->second)->traverse();
		buf.insert(buf.end(), temp.begin(), temp.end());
	}
	return buf;
}

template <typename T>
std::vector<ITree<T>*> Tree<T>::branch(std::string targetId) {
	std::vector<ITree<T>*> buf;
	if (this->identifier() == targetId) {
		buf.insert(buf.end(), this);
		return buf;
	}

	typename std::map<std::string, ITree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		std::vector<ITree<T>*> temp = (it->second)->branch(targetId);
		if (temp.size()>0) {
			buf.insert(buf.end(), this);
			buf.insert(buf.end(), temp.begin(), temp.end());
			return buf;
		}
	}
	
	return buf;
}