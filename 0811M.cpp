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
	int num, k;
	queue<int> cola;
	queue<int> resultado;
	stack<int> pila;
	cin >> num;
	while (num != -1) {
		cola.push(num);
		cin >> num;
	}
	cin >> k;

	mostrar(cola);
	if (k > cola.size()) { k = cola.size(); }
	for (int i = 0; i < k; i++) {
		pila.push(cola.front());
		cola.pop();
	}
	while (!pila.empty()) {
		resultado.push(pila.top());
		pila.pop();
	}
	while (!cola.empty()) {
		resultado.push(cola.front());
		cola.pop();
	}

	mostrar(resultado);
}

int main() {
	int ncasos;
	cin >> ncasos;
	for (int i = 0; i < ncasos; i++) {
		resuelve();
	}
	return 0;
}