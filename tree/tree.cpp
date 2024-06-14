#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "node.h"
#include "tree.h"
#include <iostream>

template <typename T>
Tree<T>::Tree() :Node<T>{} {
}

template <typename T>
Tree<T>::Tree(std::string id) :
	Node<T>(id), is_root{ false }{
};

template <typename T>
Tree<T>::Tree(std::string id, bool is_root) :
	Node<T>{ id }, is_root{ is_root }{
};

template <typename T>
Tree<T>::Tree(std::string id, T data, bool is_root) :
	Node<T>{ id, data }, is_root{ is_root } {
};

template<typename T>
Tree<T>::Tree(Tree<T>& t) : 
	Node<T>{ t._id, t._data}, is_root{t.is_root}, is_leaf{t.is_leaf}{
	typename std::unordered_map<std::string, Tree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		auto pt = it->second;
		mChildren[it->first] = new Tree<T>(*pt);
	}
};

template<typename T>
Tree<T>::Tree(Tree<T>&& t) :
	Node<T>{ t._id, t._data }, is_root{ t.is_root }, is_leaf{ t.is_leaf }{
	typename std::unordered_map<std::string, Tree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		mChildren[it->first] = it->second;
		t.mChildren[it->first] = nullptr;
	}
};

template <typename T>
Tree<T>::~Tree() {
	//std::cout << "析构Tree:" << this->identifier() << std::endl;
	typename std::unordered_map<std::string, Tree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		delete it->second;
	}
}

template<typename T>
Tree<T>& Tree<T>::operator=(Tree<T>& t) {
	this->_id = t._id;
	this->_data = t._data;
	is_root = t.is_root;
	is_leaf = t.is_leaf;

	// 回收内存
	typename std::unordered_map<std::string, Tree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		delete it->second;
	}

	// 清空
	mChildren.clear();

	for (it = t.mChildren.begin(); it != t.mChildren.end(); it++) {
		mChildren[it->first] = new Tree<T>(*it->second);
	}
	return *this;
};

// 移动子树
template<typename T>
Tree<T>& Tree<T>::operator=(Tree<T>&& t) {
	this->_id = t._id;
	this->_data = t._data;
	is_root = t.is_root;
	is_leaf = t.is_leaf;

	// 回收内存
	typename std::unordered_map<std::string, Tree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		delete it->second;
	}

	// 清空
	mChildren.clear();

	for (it = t.mChildren.begin(); it != t.mChildren.end(); it++) {
		mChildren[it->first] = it->second;
		t.mChildren[it->first] = nullptr;
	}
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
	typename std::unordered_map<std::string,Tree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		buf.push_back(it->second);
	}
	return buf;
};

// 递归查找
template <typename T>
Tree<T>* Tree<T>::search(std::string id) {
	if (id == this->_id) {
		return this;
	}

	typename std::unordered_map<std::string, Tree<T>*>::iterator foundPair = mChildren.find(id);
	if (foundPair != mChildren.end()) {
		return foundPair->second;
	}

	typename std::unordered_map<std::string, Tree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		Tree<T>* subtree = it->second;
		Tree<T>* found = subtree->search(id);
		if (found != nullptr) {
			return found;
		}
	}

	return nullptr;
};

template <typename T>
Tree<T>* Tree<T>::insert(Tree<T>* subtree) {
	std::string subid = subtree->_id;
	typename std::unordered_map<std::string, Tree<T>*>::iterator pairFound = mChildren.find(subid);
	if (pairFound != mChildren.end()) {
		return nullptr;
	}

	Tree<T>* new_subtree = new Tree<T>(*subtree);
	mChildren[subid] = new_subtree;
	if (isLeaf()) {
		is_leaf = false;
	}
	return new_subtree;
};

template <typename T>
Tree<T>* Tree<T>::insert(Tree<T>* subtree, std::string targetId) {
	Tree<T>* target = this->search(targetId);
	if (target == nullptr) {
		return nullptr;
	}
	
	return target->insert(subtree);
};

template <typename T>
Tree<T>* Tree<T>::attach(Tree<T>* subtree) {
	std::string subid = subtree->_id;
	typename std::unordered_map<std::string, Tree<T>*>::iterator pairFound = mChildren.find(subid);
	if (pairFound != mChildren.end()) {
		return nullptr;
	}
	
	mChildren[subid] = subtree;
	if (isLeaf()) {
		is_leaf = false;
	}
	return subtree;
};

template <typename T>
Tree<T>* Tree<T>::attach(Tree<T>* subtree, std::string targetId) {
	Tree<T>* target = this->search(targetId);
	if (target == nullptr) {
		return nullptr;
	}

	return target->attach(subtree);
};

// 不能remove自身
template <typename T>
bool Tree<T>::remove(std::string id) {
	// 子节点中寻找
	if (mChildren.count(id) > 0) {
		mChildren.erase(id);
		return true;
	}

	// 子节点中没有找到
	typename std::unordered_map<std::string, Tree<T>*>::iterator it;
	for (it = this->mChildren.begin(); it != this->mChildren.end(); it++) {
		Tree<T>* subtree = it->second;
		bool flag = subtree->remove(id);
		if (flag) {
			return true;
		}
	}

	return false;
};

template <typename T>
std::string Tree<T>::str() {
	std::string s = this->_id;

	if (isLeaf()) {
		s += "(leaf)";
	}

	s += ":[";

	std::vector<Tree<T>*> kids = children();
	for (std::size_t i = 0; i < kids.size(); i++) {
		Tree<T>* kid = kids[i];
		s += kid->_id;
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
	typename std::unordered_map<std::string, Tree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		std::vector<Tree<T>*> temp = (it->second)->traverse();
		buf.insert(buf.end(), temp.begin(), temp.end());
	}
	return buf;
}

template <typename T>
std::vector<Tree<T>*> Tree<T>::branch(std::string targetId) {
	std::vector<Tree<T>*> buf;
	buf.insert(buf.end(), this);

	if (this->_id == targetId) {
		return buf;
	}

	typename std::unordered_map<std::string, Tree<T>*>::iterator it;
	for (it = mChildren.begin(); it != mChildren.end(); it++) {
		std::vector<Tree<T>*> temp = (it->second)->branch(targetId);
		if (temp.size()>0) {
			buf.insert(buf.end(), temp.begin(), temp.end());
			return buf;
		}
	}
	
	return buf;
}