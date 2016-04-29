#include <iostream>
#include "Arbin.h"
#include <string>
using namespace std;

template <class T>
Arbin<T> leerArbol(T const&	vacio)	{
	T raiz;	cin >> raiz;
	if (raiz == vacio)	return Arbin<T>();
	Arbin<T> a1 = leerArbol(vacio);
	Arbin<T> a2 = leerArbol(vacio);
	return Arbin<T>(a1, raiz, a2);
}

template <class T>
void resuelve(Arbin<T> const & a, string & id, int & coste){
	int coste1, coste2;
	string id1, id2;
	//a.raiz() no es tesoro y no es vacio, ese caso lo cubrimos antes
	if (a.raiz() == "Dragon" || a.raiz() == "Via_libre"){
		
		if (a.raiz() == "Dragon") coste = 1;
		else coste = 0;

		//Como el identificador es dragon o via libre, no pueden ser los dos hijos null
		if (a.hijoDr().esVacio() ){
			resuelve(a.hijoIz(), id1, coste1);
			id = id1;
			coste += coste1;
		}
		else if (a.hijoIz().esVacio()){
			resuelve(a.hijoDr(), id2, coste2);
			id = id2;
			coste += coste2;
		}
		else {
			resuelve(a.hijoIz(), id1, coste1);
			resuelve(a.hijoDr(), id2, coste2);
			if (coste1 <= coste2){
				id = id1;
				coste += coste1;
			}
			else {
				id = id2;
				coste += coste2;
			}
		}
		return;
	}
	else{ //Es hoja
		coste = 0;
		id = a.raiz();
		return;
	}	
}

template <class T>
void resuelve(Arbin<T> const & a){
	string id1, id2;
	int coste1, coste2;

	if (a.hijoDr().esVacio()){
		resuelve(a.hijoIz(), id1, coste1);
		cout << id1 << " " << coste1 << endl;
	}
	else if (a.hijoIz().esVacio()){
		resuelve(a.hijoDr(), id2, coste2);
		cout << id2 << " " << coste2 << endl;
	}
	else {
		resuelve(a.hijoIz(), id1, coste1);
		resuelve(a.hijoDr(), id2, coste2);
		if (coste1 <= coste2){ cout << id1 << " " << coste1 << endl; }
		else cout << id2 << " " << coste2 << endl;
	}
	
}


int main(){
	int ncasos;
	cin >> ncasos;
	Arbin<string> a;
	string vacio = "...";
	for (int i = 0; i < ncasos; i++){
		a = leerArbol(vacio);
		resuelve(a);
	}


	return 0;
}