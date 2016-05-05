#include <iostream>
#include "Arbin.h"
#include <list>
#include <vector>
using namespace std;

template<class T>
int buscar(vector<T> const & in, int const & ini, int const & fin, int const & num) {

	for (int i = ini; i < fin; i++) {
		if (in[i] == num) return i;
	}
	return ini;
}

template<class T>
Arbin<T> reconstruye(vector<T> const & pre, vector<T> const & in, int const & iniInorden, int const & finInorden, int const & raiz) {

	if (iniInorden == finInorden) {
		return Arbin<T>(in[iniInorden]);
	}
	else if (iniInorden < finInorden) {
		//i es la posición donde se encuentra la raíz del arbol en la lista en inorden
		int i = buscar(in, iniInorden, finInorden, pre[raiz]);
		Arbin<T> aIz = reconstruye(pre, in, iniInorden, i - 1, raiz + 1);
		int nElemsIz = i - iniInorden;
		Arbin<T> aDr = reconstruye(pre, in, i+1, finInorden, raiz + 1 + nElemsIz);

		return Arbin<T>(aIz, pre[raiz], aDr);
	}
	else {//Esta vacio
		return Arbin<T>();
	}

}

bool resuelve() {
	int num;
	vector<int> pre;
	vector<int> in;
	//leemos la lista en preorden
	cin >> num;
	while (num != -1) {
		pre.push_back(num);
		cin >> num;
	}
	//leemos la lista en inorden
	cin >> num;
	while (num != -1) {
		in.push_back(num);
		cin >> num;
	}

	if (pre.empty()) return false;
	
	Arbin<int> a = reconstruye(pre, in, 0, in.size() - 1, 0);
	list<int> aNiveles = a.niveles();
	list<int>::const_iterator it = aNiveles.cbegin();

	for (int i = 0; i < aNiveles.size() - 1; ++i, ++it) {
		cout << *it << ' ';
	}
	cout << *it << '\n';

	return true;
}


int main() {
	while (resuelve()) {}

	return 0;
}