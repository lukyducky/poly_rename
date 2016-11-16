#ifndef _POLY_LIST_H
#define _POLY_LIST_H
#include "node.h"
#include <iostream>



template <class T>
class Poly{
public:
	Poly(); //CTOR
	Poly(const Poly<T> & Q){*this = Q;}//copy CTOR;
	~Poly(); //DTOR

	void pushFront(T d, T e);
	T popFront();
	void pushBack(T d);
	void pushB(T c, T e);
	T popBack();


	Poly<T>& fillPoly();

	Poly<T>& combinePoly();
	Poly<T>& orderPoly();
	Poly<T>& insertZeros();
	Poly<T>& prettyPoly(){
		this->orderPoly();
		this->combinePoly();
		this->insertZeros();
		return *this;
	}

	T greatestExp();
	T countCoef(int E);

	void clear();
	bool isEmpty();

	//overloading cout and <<
	friend std::ostream& operator <<(std::ostream& os, Poly<T>& q)
	{
		Node<T>* it = q.head; //node ptr to head of q.
		while (it != NULL) //while node is not null
		{
			if (it->coef != 0) //skips over 0's in the coef
			{
				os << it->coef << "x^" << it->exp << " + ";//print out the data
			}
			it = it->prev; //move the ptr down
		}
		return os; //return os
	}

	

	bool operator < (const Poly<T>& Q);
	bool operator > (const Poly<T>& Q);
	bool operator == (const Poly<T>& Q);


	Poly<T>& operator = (const Poly<T>&Q);
	Poly<T>& operator + (const Poly<T>&Q);
	Poly<T>& operator - (const Poly<T>&Q);
	Poly<T>& operator * (const Poly<T>&Q);
	Poly<T>& operator / (const Poly<T>&Q);

	friend Poly<T>& operator * (const Poly<T>&Q, T s)
	{
		Poly<T>*out = new Poly<T>;
		Node<T>* it = Q.head;

		while (it != NULL)
		{
			out->pushBack(s * it->coef);
			it = it->prev;
		}

		return *out;
	}

	friend Poly<T>& operator * (T s, const Poly<T>&Q)
	{
		Poly<T>*out = new Poly<T>;
		Node<T>* it = Q.head;

		while (it != NULL)
		{
			out->pushBack(s * it->coef);
			it = it->prev;
		}

		return *out;
	}
	T testInput()
	{
		T input;
		while (!(cin >> input)){
			cin.clear();
			cin.ignore();
			cout << "invalid input; please try again";
		}
		return input;
	}
	

private:
	Node<T>*head;
	Node<T>*tail;
	unsigned int size;
};



#endif
