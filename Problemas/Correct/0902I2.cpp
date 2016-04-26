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

int max(int const & x, int const & y) {
	if (x < y) return y;
	return x;
}

template <class T>
int altura(Arbin<T> const & arbol) {
	if (arbol.esVacio()) return 0;
	int x = altura(arbol.hijoDr());
	int y = altura(arbol.hijoIz());

	return max(x, y) + 1;
}

int main() {
	int ncasos;
	cin >> ncasos;
	Arbin<int> a;

	for (int i = 0; i < ncasos; i++) {
		a = leerArbol(-1);
		cout << altura(a) << endl;
	}
	return 0;
}