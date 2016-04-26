#include <iostream>
#include "SinglyLinkedList.h"
using namespace std;

int main() {
	int ncasos;
	cin >> ncasos;
	for (int i = 0; i < ncasos; i++) {
		SinglyLinkedList<int> lista;
		int num, k;
		cin >> num;
		while (num != -1) {
			lista.push_front(num);
			cin >> num;
		}
		cin >> k;

		lista.mostrarFormatoK();
		lista.invertirK(k);
		lista.mostrarFormatoK();
	}
	return 0;
}