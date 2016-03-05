#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
using namespace std;

class Horas {
	int h;
	int min;
	int sec;

public:

	Horas() {
		this->h = 0; this->min = 00; this->sec = 00;
	}

	Horas(const int & _h, const int & _min, const int & _sec) {
		if (0 <= _h && _h <= 23 && 0 <= _min && _min <= 59 && 0 <= _sec && _sec <= 59) {
			this->h = _h; this->min = _min; this->sec = _sec;
		}
		else { throw invalid_argument("ERROR"); }
	}

	void setFecha(const int & _h, const int & _min, const int & _sec) {
		*this = Horas(_h, _min, _sec);
	}

	int getH() { return this->h; }

	int getMin() { return this->min; }

	int getSec() { return this->sec; }

	Horas& operator = (const Horas & hC)
	{
		this->h = hC.h;
		this->min = hC.min;
		this->sec = hC.sec;
		return *this;
	}

	bool operator == (const Horas & h2) {
		if (this->h == h2.h && this->min == h2.min && this->sec == h2.sec) return true;
		return false;
	}

	bool operator !=  (const Horas & h2) {
		return !(*this == h2);
	}

	bool operator < (const Horas & h2) {
		if (this->h < h2.h) { return true; }
		else if (this->h > h2.h) { return false; }
		else if (this->h == h2.h) {
			if (this->min < h2.min) { return true; }
			else if (this->min > h2.min) { return false; }
			else if (this->min == h2.min) {
				if (this->sec < h2.sec) { return true; }
				else if (this->sec >= h2.sec) { return false; }
			}
		}
	}

	bool operator > (const Horas & h2) {
		return !(*this < h2) && *this != h2;
	}

	bool operator >= (Horas h2) {
		return !(*this < h2);
	}

	bool operator <= (Horas h2) {
		return !(*this > h2);
	}

	istream& operator >> (istream & is);
	ostream& operator << (ostream & os);

};

istream& operator >> (istream & is, Horas & hora)
{
	Horas hAux;
	char ch;
	int h, min, sec;

	is >>h >> ch >> min >> ch >> sec;
	try {
		hora = Horas(h, min, sec);
	}
	catch (invalid_argument e) {
		throw invalid_argument("ERROR");
	}
	is.ignore();

	return is;
}

ostream& operator << (ostream & os, Horas hora) {
	os << setfill('0') << setw(2) << hora.getH() << ":" << setw(2) << hora.getMin() << ":" << setw(2) << hora.getSec();
	return os;
}


int buscarOMayor(vector<Horas> tren, int ini, int fin, Horas dato) {
	if (tren[fin] < dato) { return -1; }
	
	int mitad, iteraciones = 0;
	while ((ini <= fin)) {
		mitad = (ini + fin) / 2;
		if (dato == tren[mitad]) { return mitad; }
		else if (dato < tren[mitad]) { fin = mitad - 1; }
		else { ini = mitad + 1; }
		iteraciones++;
	}
	if (tren[mitad]>dato) { return mitad; }
	else return mitad + 1;
}

void procesa(vector<Horas> tren, int ntren, Horas consulta) {

	int pos = buscarOMayor(tren, 0, ntren - 1, consulta);
	if(pos!=-1){
		cout << tren[pos] << endl;
	}
	else { cout << "NO" << endl; }

}


int main() {

	int ntrenes, ncon;
	cin >> ntrenes >> ncon;

	while (ntrenes != 0 || ncon != 0) {
		vector<Horas> tren;
		tren.reserve(100000);
		//Guardamos los trenes en el vector 
		for (int i = 0; i < ntrenes; i++) {
			Horas j;
			cin >> j;
			tren.push_back(j); 
		}

		//Procesamos las consultas
		Horas consulta;
		for (int i = 0; i < ncon; i++) {
			try {
				cin >> consulta;
				procesa(tren, ntrenes, consulta);
			}
			catch (invalid_argument e) {
				cout <<e.what() << endl;
			}
		}
		cout << "---" << endl;
		//Leemos un nuevo caso
		cin >> ntrenes >> ncon;
	}

	return 0;
}