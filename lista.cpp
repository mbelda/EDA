#include "SinglyLinkedList.h"
using namespace std;

bool resuelve() {
	int num;
	SinglyLinkedList<int> list = SinglyLinkedList<int>();
	cin >> num;
	if (num == 0) return false;
	do {
		list.push_front(num);
		cin >> num;
	} while (num != 0);

	list.duplicate();
	list.mostrar();
	return true;
}

int main() {
	
	while (resuelve()) {}
	
	return 0;
}