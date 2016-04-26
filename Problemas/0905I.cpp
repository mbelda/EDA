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
bool binario(Arbin<T> const & a, T & min, T & max) {
	bool bin = true, binAux;
	if(!a.esVacio()){
		min = a.raiz();
		max = a.raiz();

		T minAux = min, maxAux = max;
		//Hijo iz
		binAux = binario(a.hijoIz(), minAux, maxAux);
		if (maxAux > max) bin = false;
		if (minAux < min) min = minAux;
		bin = bin && binAux;

		//Hijo der
		binAux = binario(a.hijoDr(), minAux, maxAux);
		if (minAux < max) bin = false;
		if (maxAux > max) max = maxAux;
		bin = bin && binAux;
	}
	return bin;
}

bool resuelve() {
	int num;
	bool bin;
	Arbin<int> a;
	Arbin<char> c;
	

	cin >> num;
	if (!cin) return false;

	if (num == 0) {
		int min, max;
		a = leerArbol(-1);
		bin = binario(a, min, max);
		if (!a.esVacio()) { cout << min << " " << max << " "; }
		
	}
	else {
		char min, max;
		c = leerArbol('.');
		bin = binario(c, min, max);
		if (!c.esVacio()) { cout << min << " " << max << " "; }
	}
	if (bin) { cout << "SI"; }
	else { cout << "NO"; }
	cout << endl;
	return true;
}

int main() {
	while (resuelve()) {}

	return 0;
}