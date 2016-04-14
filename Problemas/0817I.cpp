#include <iostream>
#include <list>
using namespace std;
	
void mostrar(list<int> const & lista) {
	list<int>::const_reverse_iterator it = lista.crbegin();
	list<int>::const_reverse_iterator itFin = lista.crend();

	while (it != itFin) {
		cout << *it;
		++it;
	}
	cout << endl;
}

list<int> suma(list<int> num1, list<int> num2){
	list<int>::const_reverse_iterator it1 = num1.crbegin();
	list<int>::const_reverse_iterator itFin1 = num1.crend();
	list<int>::const_reverse_iterator it2 = num2.crbegin();
	list<int>::const_reverse_iterator itFin2 = num2.crend();

	list<int> suma;
	int llevamos = 0, sum;

	while (it1 != itFin1 && it2 != itFin2) {
		sum = *it1 + *it2 + llevamos;
		suma.push_back(sum%10);
		llevamos = sum / 10;
		++it1; ++it2;
		sum = 0;
	}
	while (it2 != itFin2) {
		suma.push_back(*it2 + llevamos);
		++it2;
		llevamos = 0;
	}

	while (it1 != itFin1) {
		suma.push_back(*it1 + llevamos);
		++it1;
		llevamos = 0;
	}

	if (llevamos != 0) { suma.push_back(llevamos); }


	return suma;
	
}


bool resuelve() {
	list<int> num1;
	list<int> num2;
	char ch;
	cin >> ch;
	if (!cin) return false;
	while (ch != 'F') {
		num1.push_back(ch - '0');
		cin >> ch;
	}
	cin >> ch;
	while (ch != 'F') {
		num2.push_back(ch - '0');
		cin >> ch;
	}

	mostrar(suma(num1, num2));
	return true;
}


int main() {
	while (resuelve()) {}

	return 0;
}