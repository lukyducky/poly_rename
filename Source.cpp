#include "poly_list.h"
#include <iostream>
#include <ctime>

using namespace std;


void main(){

	srand(time(NULL));

	Poly<int>  p, p1, p2, p3, p4;

	for (int i = 0; i < 5; ++i){
		p.pushBack(i);
		int r = rand() % 10;
		int q = rand() % 10;
		p1.pushB(r, q);
		p1.pushBack(5);
	} 
	p.prettyPoly();
	p1.prettyPoly();
	
	p2 = p * p1; //multipying 2 polynomials
	p3 = 4 * (p + p1); //multiplying by a scalar
	p4 = p3; //assignment operator overloader
	cout << "p: " << p << endl;// 
	cout << "p1: " << p1 << endl;// 
	
	cout << "p2:" << p2 << endl;
	cout << "p3: " << p3 << endl << endl;
	cout << "p4: " << p4.insertZeros() << endl;
	system("pause");
}