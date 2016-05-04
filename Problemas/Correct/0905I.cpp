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
bool esHoja(Arbin<T> const & a) {
	return a.hijoDr().esVacio() && a.hijoIz().esVacio();
}

template <class T>
T minimo(T const & a, T const & b) {
	if (a < b) return a;
	return b;
}

template <class T>
T maximo(T const & a, T const & b) {
	if (a > b) return a;
	return b;
}


template <class T>
bool binario(Arbin<T> const & a, T & min, T & max) {

	if(esHoja(a)){
		min = max = a.raiz();
		return true;
	}
	else if (a.hijoIz().esVacio()) {
		T minDr, maxDr;
		bool okDr = binario(a.hijoDr(), minDr, maxDr);
		min = minimo(minDr, a.raiz());
		max = maximo(maxDr, a.raiz());
		return okDr && a.raiz() < minDr;
	}
	else if (a.hijoDr().esVacio()) {
		T minIz, maxIz;
		bool okIz= binario(a.hijoIz(), minIz, maxIz);
		min = minimo(minIz, a.raiz());
		max = maximo(maxIz, a.raiz());
		return okIz && a.raiz() > maxIz;
	}
	else { //los dos hijos son no vacios
		T minDr, maxDr, minIz, maxIz;
		bool okIz = binario(a.hijoIz(), minIz, maxIz);
		bool okDr = binario(a.hijoDr(), minDr, maxDr);
		T minAux = minimo(minDr, a.raiz());
		min = minimo(minIz, minAux);
		T maxAux = maximo(maxDr, a.raiz());
		max = maximo(maxIz, maxAux);

		return okIz && okDr && maxIz < a.raiz() && a.raiz() < minDr;
	} 

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
		if (a.esVacio()) { bin = true; }
		else{
			bin = binario(a, min, max);
			cout << min << " " << max << " ";
		}
		
	}
	else {
		char min, max;
		c = leerArbol('.');
		if (c.esVacio()) { bin = true; }
		else {
			bin = binario(c, min, max);
			cout << min << " " << max << " ";
		}
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