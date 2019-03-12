#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <list>
using namespace std;

void resuelve(list<string> const & lista, stack<string> & cola, int const & ncoches, int const & tiempo) {
	long long int tiempoT = 0;
	stack<string> carril;
	list<string>::const_iterator it = lista.cbegin();
	list<string>::const_iterator itFin = lista.cend();

	

	while (!cola.empty() || !carril.empty()) {
		
		while (it != itFin) {
			
			if (!cola.empty() && *it == cola.top()) {
				cola.pop();
				++it;
			}else if (!carril.empty() && carril.top() == *it) {
				carril.pop();
				++it;
			}else if(!cola.empty()) {
				carril.push(cola.top());
				cola.pop();
				tiempoT += tiempo;
			}
			else {
				while (!carril.empty()) {
					cola.push(carril.top());
					carril.pop();
				}
			}
	}
		
	}

	cout << tiempoT << endl;
}



int main() {
	int ncoches, tiempo;
	cin >> ncoches;
	while (cin) {
		cin >> tiempo;
		list<string> lista;
		string matricula;
		for (int i = 0; i < ncoches; i++) {
			cin >> matricula;
			lista.push_front(matricula);
		}

		stack<string> cola;
		for (int i = 0; i < ncoches; i++) {
			cin >> matricula;
			cola.push(matricula);
		}

		resuelve(lista, cola, ncoches, tiempo);
		cin >> ncoches;

	}

	return 0;
}