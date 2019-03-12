#include <iostream>
#include <cmath>
#include <string>
using namespace std;
template <class T>
class Complejo {
	T a, b;

public:
	Complejo() {}
	Complejo(T const & _a, T const & _b) {
		a = _a; b = _b;
	}

	Complejo(T const & _a) {
		a = _a; b = 0;
	}

	Complejo & operator +(Complejo const & c) {
		T a1, b1;
		a1 = a + c.a;
		b1 = b + c.b;

		return Complejo(a1, b1);
	}

	Complejo & operator *(Complejo const & c) {
		T a1, b1;
		a1 = a*c.a - b*c.b;
		b1 = a*c.b + b*c.a;
		return Complejo(a1, b1);
	}

	void setA(int const & _a) { a = _a; }
	void setB(int const & _b) { b = _b; }

	int modulo() const {
		return sqrt(a*a + b*b);
	}
};

template <class T>
string resuelve(Complejo<T> const & c, int const & iteraciones) {
	Complejo<T> z0 = Complejo<T>(0,0), z;

	for (int i = 0; i < iteraciones; i++) {
		z = z0*z0 + c;
		if (z.modulo() > 2) return "NO";
		z0 = z;
	}
	return "SI";

}


int main() {
	int ncasos;
	cin >> ncasos;
	
	Complejo<float> c;
	float a, b;
	int iteraciones;
	for (int i = 0; i < ncasos; i++) {
		cin >> a >> b >> iteraciones;
		c.setA(a);
		c.setB(b);
		cout << resuelve(c, iteraciones) << endl;
	}

	return 0;
}