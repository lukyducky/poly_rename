#include "poly_list.h"
#include <iostream>
#include <cassert>
using namespace std;


template <class T>
Poly<T>::Poly() //CTOR for an empty Poly
{
	size = 0;
	head = NULL;
	tail = NULL;
}



template <class T>
Poly<T>::~Poly() //DTOR using clear
{
	clear();
}
/*
template <class T>
void Poly<T>::pushFront(T d, T e)
{
	Node<T>* n = new Node<T>(d, e);
	if (isEmpty()){ //if it's empty
		head = n;
		tail = n;
	}
	else{
		n->prev = head;
		head->next = n;
		head = head->next;
	}
	size++;
}
*/
template <class T>
T Poly<T>::popFront()
{
	assert(!isEmpty());

	T d = head->coef;

	if (size == 1) { //if this is the last node
		delete head;
		head = tail = NULL;
	}

	else{
		head = head->prev;
		delete head->next;
		head->next = NULL;
	}
	size--;
	return d;
}

template <class T>
void Poly<T>::pushBack(T d)
{
	Node<T>* n = new Node<T>;
	n->coef = d;
	if (isEmpty()){ //if it's empty
		head = n;
		tail = n;
		n->exp = 0;
	}
	else{
		n->exp = tail->exp + 1;
		n->next = tail;
		tail->prev = n;
		tail = tail->prev;
	}
	size++;
}

template <class T>
void Poly<T>::pushB(T c, T e)
{
	Node<T>* n = new Node<T>;
	n->coef = c;
	n->exp = e;
	if (isEmpty()){ //if it's empty
		head = n;
		tail = n;
	}
	else{
		n->next = tail;
		tail->prev = n;
		tail = tail->prev;
	}
	size++;
}


template <class T>
T Poly<T>::popBack()
{
	assert(!isEmpty());


	T d = tail->coef; //saving the data at the thing we want

	if (size == 1) { //if this is the last node
		delete head;
		head = tail = NULL;
	}

	else{
		tail = tail->next;
		delete tail->prev;
		tail->prev = NULL;
	}
	size--; //decrement size
	return d; //returning data
}


template <class T>
void Poly<T>::clear()
{
	while (!isEmpty()){
		popFront();
	}
}

template <class T>
bool Poly<T>::isEmpty()
{
	return (size == 0) ? true : false;
}

template <class T>
Poly<T>& Poly<T>::fillPoly() //not done yet; but: fill a polynomial using user input
{
	this->clear(); //get rid of whatever is in this;
	Poly<T>*out = new Poly<T>;
	T coef, exp;
	cout << "inputting polynomial:" << endl << "enter highest power:";
	exp = testInput();
	cout << "enter coefficients, hit enter between terms:";
	for (int i = 0; i < exp + 1; i++)
	{
		coef = testInput();
		out->pushBack(coef);
	}

	*this = *out;
	delete out;
	return *this;
}


template <class T>
Poly<T>& Poly<T>::operator = (const Poly<T>&Q) //assignment overloader: sets the lhs poly to the rhs poly
{
	this->clear(); //get rid of stuff in lhs poly

	Node<T>* it = Q.head; //ptr to rhs head
	while (it != NULL) //loop throuhg rhs poly
	{
		this->pushB(it->coef, it->exp); //push onto lhs using pushB
		it = it->prev; //move ptr down
	}
	return *this;
}

template <class T>
bool Poly<T>:: operator < (const Poly<T>& Q) //comparing size: only works if polys have been sorted.
{
	bool A = true;
	if (this->tail->exp < Q.tail->exp)
	{
		A = false;
	}
	return A;
}

template <class T>
bool Poly<T>:: operator >(const Poly<T>& Q) //comparing size: only works if polys have been sorted.
{
	bool A = false;
	if (this->tail->exp > Q.tail->exp)
	{
		A = true;
	}
	return A;
}

template <class T>
bool Poly<T>::operator == (const Poly<T>& Q) //comparing size: only works if polys have been sorted.
{
	bool A = true;
	if (this->tail->exp != Q.tail->exp){ A = false; }
	else
	{
		Node<T>* th = this->head;
		Node<T>* it = Q.head;
		while (it != NULL) //loop through rhs
		{
			if (it->coef != th->coef || it->exp != th->exp){ A = false; }
			//move ptrs down
			it = it->prev;
			th = th->prev;
		}
	}
	return A;
}

template <class T>
Poly<T>& Poly<T>::operator + (const Poly<T>&Q) //adds polynomials together; only works if poly has been sorted AND has zeroes added in
{
	//creating ptrs for reference 
	Poly<T>*out = new Poly<T>;
	Node<T>* th = this->head;
	Node<T>* it = Q.head;
	if (this->size < Q.size)//if lhs poly is smaller than rhs
	{
		while (th != NULL)//loop through lhs poly
		{
			out->pushBack(th->coef + it->coef); //use pushBack to put sum into out
			//moves ptrs down
			it = it->prev;
			th = th->prev;
		}
		while (it != NULL) //loop through rest of rhs poly
		{
			out->pushBack(it->coef); //put inot out
			it = it->prev; //move ptrs down
		}
	}

	if (this->size >= Q.size)//if lhs poly is smaller than rhs
	{
		while (it != NULL) //loop through rhs poly
		{
			out->pushBack(th->coef + it->coef); //uses pushBack to put sum into out
			it = it->prev;
			th = th->prev;
		}
		while (th != NULL)//uses pushBack to put rest of lhs into out
		{
			out->pushBack(th->coef);
			th = th->prev;
		}
	}

	return *out;
}

template <class T>
Poly<T>& Poly<T>::operator - (const Poly<T>&Q) //subtracts polynomials together; only works if poly has been sorted AND has zeroes added in
{
	//creating ptrs for reference 
	Poly<T>*out = new Poly<T>;
	Node<T>* th = this->head;
	Node<T>* it = Q.head;
	if (this->size < Q.size) //if lhs poly is smaller than rhs
	{
		while (th != NULL) //going through every element in lhs poly
		{
			out->pushBack(th->coef - it->coef); //using pushBack to put difference into out
			//move ptrs down
			it = it->prev;
			th = th->prev;
		}
		while (it != NULL) //goes through elements in rhs
		{
			out->pushBack(it->coef);
			it = it->prev; //move ptrs down
		}
	}

	if (this->size >= Q.size)//if lhs poly is bigger or equal to than rhs
	{
		while (it != NULL) //loop throuhg rhs
		{
			out->pushBack(th->coef - it->coef);  //use pushBack to put difference into out
			//moves ptr back
			it = it->prev;
			th = th->prev;
		}
		while (th != NULL) //loop through the rest of lhs
		{
			out->pushBack(th->coef); //add from lhs poly to out
			th = th->prev; //move ptr back
		}
	}

	return *out;
}

template <class T>
Poly<T>& Poly<T>::operator * (const Poly<T>&Q) //use pretty poly on both before multiplying!!
{
	//ptrs for reference
	Poly<T>*out = new Poly<T>;
	Node<T>* th = this->head;
	Node<T>* it;

	while (th != NULL) //loop through lhs poly
	{
		it = Q.head; //starting from top of rhs poly
		while (it != NULL) //and loop through
		{
			out->pushB(th->coef * it->coef, th->exp + it->exp); //use pushB to put the product into out
			it = it->prev;	 //move it ptr down: rhs poly
		}
		th = th->prev; //move th ptr down: lhs poly
	}
	out->prettyPoly();

	return *out; //return answer
}


template <class T>
Poly<T>& Poly<T>::combinePoly() //groups like terms and combines them. 
{
	//PTRS
	Poly<T>*out = new Poly<T>; 
	Node<T>* it = new Node<T>;
	Node<T>*p1;
	Node<T>* th = this->head;

	int cnt = 0, coef;

	while (th != NULL){ //loops through the polynomial twice to compare its parts
		coef = 0;
		it = this->head;
		while (it != NULL){
			//coef = 0;
			if (it->exp == th->exp && it != th){ //IT DOES THE THING: combines like terms
				//coef = 0;
				cnt = countCoef(it->exp); //get # of coef the exp
				p1 = it; //hold it
				//adds the coefficients together
				for (int i = 1; i < cnt; i++){ //goes through for as many coef there are for that exp
					if (i == 1){coef += th->coef; } //so it will get the first one
					coef += it->coef; //adds to coef
					if (it->prev != NULL){ it = it->prev; } //moves it down 
					else{ break; }
				}
				it = p1;//return it to before the for loop usin p1
				//pushes it into the polynomial
				if (out->tail == NULL){ //if out doesn't have anything in it yet, push into it
					out->pushB(coef, it->exp);
				}
				else if (out->tail->coef != coef && out->tail->exp != it->exp){ //checks if the exact same thing is already inside
					out->pushB(coef, it->exp);
				}
					//coef = 0;
			}
			else if (it->exp == th->exp && it == th && countCoef(it->exp) == 1){ //adds the parts that do not need combining
				out->pushB(it->coef, it->exp);
			}
			it = it->prev; //move ptr back
		}
		th = th->prev; //move ptr back
	}
	*this = *out;
	delete out;
	return *this; //return the outcome
}

template <class T>
Poly<T>& Poly<T>::orderPoly() //puts elements of polynomial in order via exponents; does not account for coefficients
{
	Poly<T>*out = new Poly<T>;
	Node<T>*it;
	int cnt = this->greatestExp() + 1; //get greatest exp
	for (int i = 0; i < cnt; i++) //loop using cnt
	{
		it = this->head; //start at head of this poly
		while (it != NULL) //and loop through
		{
			if (i == it->exp) //if the exp is same as cnt
			{
				out->pushB(it->coef, it->exp); //push onto out
			}
			it = it->prev;//move ptr down
		}
	}
	*this = *out;
	delete out;
	return *this;
}

template <class T>
T Poly<T>::greatestExp() //gets greatest exponent of the polynomial
{
	Node<T>*it = this->head; //ptr to head of poly
	T great = 0;//this->tail->exp;
	while (it != NULL){ //looping thoguh
		if (it->exp > great){ //if the exp is greater than great
			great = it->exp; //set great to exp
		}
		it = it->prev; //move ptr down
	}
	return great; //return great(est exponent)
}

template <class T>
T Poly<T>::countCoef(int E){ //counts the terms of the Eth power
	int cnt = 0;
	Node<T>*it = this->head;
	while (it != NULL){
		if (it->exp == E){ cnt++; } //if exp is same, up the count
		it = it->prev; //move back
	}
	return cnt; //return count
}


template <class T>
Poly<T>& Poly<T>::insertZeros() //use AFTER sort 
{
	//PTRs and variables
	Poly<T>*out = new Poly<T>;
	Node<T>*it;
	int count, exp;

	exp = this->greatestExp() + 1; //gets the greatest exp; 

	for (int i = 0; i < exp; i++){ //loops through to create a polynomial of size of greatest exp
		count = this->countCoef(i); //counts the numbers of terms the exp has; is either 0 or 1 because of combine poly
		if (count == 0){ //if there's no terms of that exp, push 0
			out->pushBack(0);
		}
		else{ //if it is 1, 
			it = this->head;
			while (it != NULL){ //loop through the poly to find that term
				if (it->exp == i){ 
					out->pushB(it->coef, it->exp); //add coefficient to the poly
					break; //get out of the loop; no point continuing
				}
				it = it->prev;
			}
		}
	}
	*this = *out;
	delete out;
	return *this;
}



//explicit instantiations with templates
template class Poly<int>;
//template class Poly<float>;

//template class Poly<double>;
