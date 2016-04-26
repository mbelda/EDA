#include <iostream>
#include <stack>
#include <queue>
using namespace std;


void mostrar(queue<int> cola) {
	cout << "{";
	int n = cola.size();
	for (int i = 0; i < n; i++) {
		cout << cola.front();
		cola.pop();
		if (i + 1 != n) cout << ",";
	}
	cout << '}' << endl;

}


void resuelve() {
	int num, pringao;
	queue<int> cola;
	queue<int> amigos;
	queue<int> resultado;

	cin >> num;
	while (num != -1) {
		cola.push(num);
		cin >> num;
	}
	cin >> pringao;
	cin >> num;
	while (num != -1) {
		amigos.push(num);
		cin >> num;
	}

	mostrar(cola);

	if (pringao <= cola.size()) {
		for (int i = 0; i < pringao; i++) {
			resultado.push(cola.front());
			cola.pop();
		}
		while (!amigos.empty()) {
			resultado.push(amigos.front());
			amigos.pop();
		}
		while (!cola.empty()) {
			resultado.push(cola.front());
			cola.pop();
		}
		mostrar(resultado);
	}
	else { mostrar(cola); }

	
}

int main() {
	int ncasos;
	cin >> ncasos;
	for (int i = 0; i < ncasos; i++) {
		resuelve();
	}
	return 0;
}