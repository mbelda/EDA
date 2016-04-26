#include<iostream>
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

template <class T, class funcion>
int nNodosCumplenF(Arbin<T> const & arbol, funcion const & f) {
	int cont = 0;
	if (arbol.esVacio()) return 0;
	if (f(arbol.raiz())) cont++;
	cont += nNodosCumplenF(arbol.hijoIz(), f);
	cont += nNodosCumplenF(arbol.hijoDr(), f);
	return cont;
}

int main() {
	int ncasos, numero;
	cin >> ncasos;
	Arbin<int> a;



	for (int i = 0; i < ncasos; i++) {
		cin >> numero;
		auto requisitos = [numero](int num) -> bool {
			return num % numero == 0;
		};
		a = leerArbol(-1);
		cout << nNodosCumplenF(a, requisitos) << endl;
	}
	return 0;
}