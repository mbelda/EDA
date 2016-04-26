#include <list>
#include <iostream>
using namespace std;

void duplicar(list<int> & lista) {
	auto it = lista.cbegin();
	auto itFin = lista.cend();

	list<int> aux;

	while (it != itFin) {
		aux.push_back(*it);	
		aux.push_back(*it);
		it++;
	}

	lista = aux;
}


void mostrar(list<int> const & lista) {
	auto it = lista.cbegin();
	auto itFin = lista.cend();

	while (it != itFin) {
		cout << *it;
		if (++it != itFin) { cout << " "; }
	}

	cout << endl;

}



int main() {
	int num;
	cin >> num;
	while (true) {
		if (num == 0) return 0;
		list<int> lista;
		while (num != 0) {
			lista.push_front(num);
			cin >> num;
		}

		duplicar(lista);
		mostrar(lista);

		cin >> num;
	}

	return 0;
}