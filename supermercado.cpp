#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int colocar(int const & persona, vector<int> & caja1, vector<int> & caja2, vector<int> & caja3, int & suma1, int & suma2, int & suma3) {
	if (suma1 <= suma2 &&suma1 <= suma3) {
		caja1.push_back(persona);
		suma1 += persona;
		return 1;
	}
	else if (suma2 <= suma3) {
		caja2.push_back(persona);
		suma2 += persona;
		return 2;
	}
	else {
		caja3.push_back(persona);
		suma3 += persona;
		return 3;
	}
}


int resolver(int const & posVecinoAnterior, int const & posVecino, queue<int> & cola, vector<int> & caja1, vector<int> & caja2, vector<int> & caja3, int & suma1, int & suma2, int & suma3) {
	int caja;
	for (int i = posVecinoAnterior; i < posVecino; i++) {
		caja = colocar(cola.front(), caja1, caja2, caja3, suma1, suma2, suma3);
		cola.pop();
	}
	return caja;
}


void resuelve(queue<int> & cola, int & ncola, vector<int> const & vecinos) {
	vector<int> caja1, caja2, caja3;
	int suma1 = 0, suma2 = 0, suma3 = 0;
	int valor;
	for (int i = 0; i < vecinos.size(); i++) {
		if (i == 0)valor = 0;
		else { valor = vecinos[i - 1]; }
		cout << resolver(valor, vecinos[i], cola, caja1, caja2, caja3, suma1, suma2, suma3);
		if (i != vecinos.size() - 1) { cout << " "; }
	}
	cout << endl;
}


int main() {
	int ncola, nvecinos;
	cin >> ncola >> nvecinos;
	while (ncola != 0) {
		queue<int> cola;
		int tiempo;
		for (int i = 0; i < ncola; i++) {
			cin >> tiempo;
			cola.push(tiempo);
		}
		vector<int> vecinos;
		int posVecino;
		for (int i = 0; i < nvecinos; i++) {
			cin >> posVecino;
			vecinos.push_back(posVecino);
		}

		resuelve(cola, ncola, vecinos);

		cin >> ncola >> nvecinos;
	}

	return 0;
}