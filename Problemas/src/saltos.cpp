#include <iostream>
#include "SinglyLinkedList.h"
using namespace std;

int main() {
	int n;
	cin >> n;
	while (n != 0) {
		SinglyLinkedList<int> lista;
		int num;
		cin >> num;
		while (num != 0) {
			lista.push_front(num);
			cin >> num;
		}
		lista.saltos(n);
		lista.mostrar();
		cout << endl;
		cin >> n;
	}
	return 0;
}