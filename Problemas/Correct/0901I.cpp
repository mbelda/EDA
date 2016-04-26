#include<iostream>
#include "Arbin.h"
using namespace std;

template <class T>
Arbin<T>	leerArbol(T const&	vacio)	{
	T raiz;	cin >> raiz;
	if (raiz == vacio)	return Arbin<T>();
	Arbin<T> a1 = leerArbol(vacio);
	Arbin<T> a2 = leerArbol(vacio);
	return Arbin<T>(a1, raiz, a2);
}


int main(){
	int ncasos, numero;
	cin >> ncasos;
	Arbin<int> a;

	

	for (int i = 0; i < ncasos; i++){
		cin >> numero;
		auto requisitos = [numero](int num) -> bool {
			return num % numero == 0;
		};
		a = leerArbol(-1);
		cout << a.nNodosCumplenF(requisitos) << endl;
	}
	return 0;
}