#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
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

	Horas(const int & seg) {
		int hAux = 0;
		int minAux = 0;
		int secAux = seg;

		//Vemos si los segundos suman minutos
		minAux += secAux / 60;
		secAux = secAux % 60;

		//Vemos si los minutos suman horas
		hAux += minAux / 60;
		minAux = minAux % 60;

		if (hAux <= 23 && minAux <= 59 && secAux <= 59) {
			h = hAux;
			min = minAux;
			sec = secAux;
		}
		else { throw invalid_argument("ERROR"); }

	}

	const int numSegundos() const {
		int segundos = 0;
		segundos += sec;
		segundos += min * 60;
		segundos += h * 60 * 60;
		return segundos;
	}

	const int getH() const { return h; }

	const int getMin() const { return min; }

	const int getSec() const { return sec; }

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

	Horas operator - (const Horas & h2) const {

		int hora1 = numSegundos(), hora2 = h2.numSegundos();
		int resta = hora1 - hora2;
		if (resta >= 0)return Horas(resta);
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

bool resuelveDato() {
	int nhoras;
	cin >> nhoras;
	if (nhoras == 0)return false;
	else {

		//Leemos los datos

		vector<Horas> v;
		for (int i = 0; i < nhoras; i++) {
			Horas j;
			try {
				// >> puede lanzar excepcion
				cin >> j;
				v.push_back(j);
			}
			catch (invalid_argument e) {}
		}

		//Resolvemos y mostramos la solucion
		sort(v.begin(), v.end());

		int indice = 0;
		Horas tiempo = Horas(0, 0, 0);

		for (int i = 0; i < v.size() - 1; i++) {
			if (tiempo < v[i + 1] - v[i]) {
				tiempo = v[i + 1] - v[i];
				indice = i;
			}
		}

		cout << v[indice] << " " << tiempo << endl;

		return true;
	}
}



int main() {

	while (resuelveDato()) {}

	return 0;
}