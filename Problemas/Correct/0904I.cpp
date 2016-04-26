#include <iostream>
#include "Arbin.h"
using namespace std;

template <class T>
Arbin<T> leerArbol(T const&	vacio) {
	T raiz;	cin >> raiz;
	if (raiz == vacio)	return Arbin<T>();
	Arbin<T> a1 = leerArbol(vacio);
	Arbin<T> a2 = leerArbol(vacio);
	return Arbin<T>(a1, raiz, a2);
}

template <class T>
int minimo(Arbin<T> const & a) {
	int min, x, y;
	if (a.esVacio()) {
		throw domain_error("arbol vacio");
	}
	min = a.raiz();
	try{
		x = minimo(a.hijoDr());
	}
	catch (domain_error e) {
		x = -1;
	}
	try {
		y = minimo(a.hijoIz());
	}
	catch (domain_error e) {
		y = -1;
	}

	if (x != -1 && x < min) min = x;
	if (y != -1 && y < min) min = y;
	return min;
	
}


int main() {
	int ncasos;
	cin >> ncasos;
	Arbin<int> a;

	for (int i = 0; i < ncasos; i++) {
		a = leerArbol(-1);
		try{
			cout << minimo(a);
		}
		catch (domain_error e) {}
		cout << endl;
	}
	return 0;
}