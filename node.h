#ifndef _NODE_H
#define _NODE_H

#include <utility>

template <class T>
class Node{
public:
	Node(){
		coef = 0;
		exp = 0;
		next = prev = 0;
	}
	Node(T c, T e){ 
		coef = c;
		exp = e;
		next = prev = 0;
	}

	T coef;
	T exp;
	Node<T> *next;
	Node<T> *prev;
};


#endif 
