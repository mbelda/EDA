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
void frontera(Arbin<T> const & arbol) {
	if (arbol.esVacio()) return;
	if (arbol.hijoDr().esVacio() && arbol.hijoIz().esVacio()) {
		cout << arbol.raiz();
	}
	else {
		frontera(arbol.hijoIz());
		frontera(arbol.hijoDr());
	}	
}

int main() {
	int ncasos;
	cin >> ncasos;
	Arbin<char> a;

	for (int i = 0; i < ncasos; i++) {
		a = leerArbol('.');
		frontera(a);
		cout << endl;
	}
	return 0;
}