#include <iomanip>
#include <string>
#include <algorithm>
#include <iostream>
#include "SinglyLinkedList.h"
using namespace std;

class Horas {
	int h;
	int min;
	int sec;

public:
	Horas() {}

	Horas(const int & _h, const int & _min, const int & _sec) {
		if (0 <= _h && _h <= 23 &&
			0 <= _min && _min <= 59 &&
			0 <= _sec && _sec <= 59) {
			h = _h; min = _min; sec = _sec;
		}
		else { throw invalid_argument("ERROR"); }
	}

	int getH() const { return h; }

	int getMin() const { return min; }

	int getSec() const { return sec; }

	Horas operator + (const Horas & h2) const {
		Horas suma;
		int hAux = h + h2.h;
		int minAux = min + h2.min;
		int secAux = sec + h2.sec;

		//Vemos si los segundos suman minutos
		minAux += secAux / 60;
		secAux = secAux % 60;

		//Vemos si los minutos suman horas
		hAux += minAux / 60;
		minAux = minAux % 60;

		if (hAux <= 23 && minAux <= 59 && secAux <= 59) {
			suma.h = hAux;
			suma.min = minAux;
			suma.sec = secAux;
			return suma;
		}
		else { throw invalid_argument("ERROR"); }

	}

	bool operator == (const Horas & h2) const {
		if (h == h2.h && min == h2.min && sec == h2.sec) return true;
		return false;
	}

	bool operator < (const Horas & h2) const {
		if (h < h2.h) { return true; }
		else if (h == h2.h) {
			if (min < h2.min) { return true; }
			else if (min == h2.min) {
				if (sec < h2.sec) { return true; }
			}
		}
		return false;
	}

	friend istream& operator >> (istream & is, Horas & hora);
	friend ostream& operator << (ostream & os, const Horas & hora);

};

istream& operator >> (istream & is, Horas & hora)
{
	Horas hAux;
	char ch;
	int h, min, sec;

	is >> h >> ch >> min >> ch >> sec;
	hora = Horas(h, min, sec);
	is.ignore();

	return is;
}

ostream& operator << (ostream & os, const Horas & hora) {
	os << setfill('0') << setw(2) << hora.getH() << ":" << setw(2) << hora.getMin() << ":" << setw(2) << hora.getSec();
	return os;
}

bool resuelveCaso() {
	int n;
	cin >> n;
	if (!cin) return false;
	SinglyLinkedList<Horas> list = SinglyLinkedList<Horas>();
	Horas h;
	for (int i = 0; i < n; i++) {
		cin >> h;
		list.push_front(h);
	}
	list.creciente();

	list.mostrar();
	cout << endl;

	return true;
}



int main() {

	while (resuelveCaso()) {}
	return 0;
}