#include "SinglyLinkedList.h"
using namespace std;

bool resuelve() {
	int ndatos, num;
	SinglyLinkedList<int> list = SinglyLinkedList<int>();
	cin >> ndatos;
	if (!cin) return false;
	for (int i = 0; i < ndatos; i++) {
		cin >> num;
		list.push_front(num);
	}

	list.mostrar();
	cout << endl;

	list.invertir();

	list.mostrar();
	cout << endl;

	return true;
}

int main() {

	while (resuelve()) {}

	return 0;
}