#ifndef _POLY_H
#define _POLY_H

#include "list.h"


template <class T>
class poly{
public:
	poly();
	~poly();

	void fillPoly(T c, T e);
	T findCoeff(T d); //to return coefficient of that power


	//operator overloading




private:
	list<T> poly;

};

#endif