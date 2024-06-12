#pragma once
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include "node.h"
#include "tree.h"
#include <iostream>

template <typename T>
Tree<T>::Tree() :Node<T>{} {
}

template <typename T>
Tree<T>::Tree(std::string id_) :
	Node<T>(id_), is_root{ false }, is_leaf{true}{
};

template <typename T>
Tree<T>::Tree(std::string id_, bool is_root) :
	Node<T>{ id_ }, is_root{ is_root }, is_leaf{ true } {
};

template <typename T>
Tree<T>::Tree(std::string id_, T data_, bool is_root) :
	Node<T>{ id_, data_ }, is_root{ is_root }, is_leaf{ true } {
};

template <typename T>
Tree<T>::Tree(std::string id_, T* pData_, bool is_root) :
	Node<T>{ id_, pData_ }, is_root{ is_root }, is_leaf{ true } {
};

template<typename T>
Tree<T>::Tree(Tree<T>& t) : 
	Node<T>{ t.identifier()}, is_root{ t.is_root }, is_leaf{t.is_leaf}, mChildren(t.mChildren){
};

template <typename T>
Tree<T>::~Tree() {
	std::cout << "析构Tree:" << this->identifier() << std::endl;
	typename std::map<std::string, Tree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		auto pt = it->second;
		delete pt;
	}
}

template<typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& t) {
	setId(t.identifier());
	setData(t.data());
	is_root = t.is_root;
	is_leaf = t.is_leaf;
	mChildren.clear();
	mChildren(t.mChildren);
	return *this;
};

template <typename T>
bool Tree<T>::isRoot() {
	return is_root;
};

template <typename T>
bool Tree<T>::isLeaf() {
	return is_leaf;
};

// 这里有错误
template <typename T>
std::vector<Tree<T>*> Tree<T>::children() {
	std::vector<Tree<T>*> buf;
	typename std::map<std::string,Tree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		buf.push_back(it->second);
	}
	return buf;
};

// 递归查找
template <typename T>
Tree<T>* Tree<T>::search(std::string id_) {
	if (id_ == this->identifier()) {
		return this;
	}

	typename std::map<std::string, Tree<T>*>::iterator foundPair = mChildren.find(id_);
	if (foundPair != mChildren.end()) {
		return foundPair->second;
	}

	typename std::map<std::string, Tree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		Tree<T>* subtree = it->second;
		Tree<T>* found = subtree->search(id_);
		if (found != nullptr) {
			return found;
		}
	}

	return nullptr;
};

template <typename T>
Tree<T>* Tree<T>::insert(Tree<T>& subtree) {
	std::string subid = subtree.identifier();
	typename std::map<std::string, Tree<T>*>::iterator pairFound = mChildren.find(subid);
	if (pairFound != mChildren.end()) {
		return nullptr;
	}

	mChildren[subid] = &subtree;
	if (isLeaf()) {
		is_leaf = false;
	}
	return &subtree;
};

template <typename T>
Tree<T>* Tree<T>::insert(Tree<T>& subtree, std::string targetId) {
	Tree<T>* target = this->search(targetId);
	if (target == nullptr) {
		return nullptr;
	}
	
	return target->insert(subtree);
};

// 不能remove自身
template <typename T>
bool Tree<T>::remove(std::string id) {
	// 子节点中寻找
	if (this->mChildren.count(id) > 0) {
		Tree<T>* subtree = this->mChildren[id];
		this->mChildren.erase(id);
		return true;
	}

	// 子节点中没有找到
	typename std::map<std::string, Tree<T>*>::iterator it;
	for (it = this->mChildren.begin(); it != this->mChildren.end(); it++) {
		Tree<T>* subtree = it->second;
		int count = subtree->remove(id);
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

	std::vector<Tree<T>*> kids = children();
	for (std::size_t i = 0; i < kids.size(); i++) {
		Tree<T>* kid = kids[i];
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
std::vector<Tree<T>*> Tree<T>::traverse() {
	std::vector<Tree<T>*> buf{this};
	typename std::map<std::string, Tree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		std::vector<Tree<T>*> temp = (it->second)->traverse();
		buf.insert(buf.end(), temp.begin(), temp.end());
	}
	return buf;
}

template <typename T>
std::vector<Tree<T>*> Tree<T>::branch(std::string targetId) {
	std::vector<Tree<T>*> buf;
	if (this->identifier() == targetId) {
		buf.insert(buf.end(), this);
		return buf;
	}

	typename std::map<std::string, Tree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		std::vector<Tree<T>*> temp = (it->second)->branch(targetId);
		if (temp.size()>0) {
			buf.insert(buf.end(), this);
			buf.insert(buf.end(), temp.begin(), temp.end());
			return buf;
		}
	}
	
	return buf;
}