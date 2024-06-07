#pragma once
#include <string>

template <typename T>
class INode {
public:
	virtual ~INode()= 0;
	virtual const std::string identifier() = 0;
	virtual T* data() = 0;
	virtual void setData(T*) = 0;
	virtual bool equal(INode<T>* n) = 0;
};

template <typename T>
INode<T>::~INode(){
}