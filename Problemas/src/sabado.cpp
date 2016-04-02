#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <string>
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
		else {throw invalid_argument("ERROR");}

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

class Pelicula {
	string titulo;
	Horas finaliza;

public:

	Pelicula() {}

	Pelicula(const string & tit, const Horas & fin) {
		titulo = tit;
		finaliza = fin;
	}

	bool operator < (const Pelicula & p2) const {
		if (finaliza < p2.finaliza) return true;
		else if (finaliza == p2.finaliza) {
			if (titulo < p2.titulo) return true;
		}
		return false;
	}
	
	friend istream& operator >> (istream & is, Pelicula & peli);
	friend ostream& operator << (ostream & os, const Pelicula & peli);

};

istream& operator >> (istream & is, Pelicula & peli) {
	Horas empieza, duracion;
	string titulo;
	is >> empieza >> duracion;
	getline(is, titulo);

	Horas finaliza = empieza + duracion;
	peli = Pelicula(titulo, finaliza);

	return is;
}

ostream& operator << (ostream & os, const Pelicula & peli) {
	os << peli.finaliza <<" " << peli.titulo;
	return os;
}


void resuelveDato(int npelis) {
	vector<Pelicula> pelis;

	//Guardamos los peliculas en el vector 
	for (int i = 0; i < npelis; i++) {
		Pelicula j;
		try{
			cin >> j;
			pelis.push_back(j);
		}
		catch (invalid_argument e) {}
	}

	//Procesamos las peliculas
	sort(pelis.begin(), pelis.end());

	//Mostramos la solución
	for (int i = 0; i < pelis.size(); i++) {
		cout << pelis[i] << endl;
	}
	cout << "---" << endl;
}

int main() {

	int npelis;
	cin >> npelis;

	while (npelis != 0) {
		resuelveDato(npelis);
		//Leemos un nuevo caso
		cin >> npelis;
	}

	return 0;
}