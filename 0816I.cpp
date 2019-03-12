#include <iostream>
#include <string>
#include <list>
using namespace std;

class Persona {
	string nombre;
	int edad;

public:

	void setEdad(int const & ed) { edad = ed; }
	void setNombre(string const & n) { nombre = n; }

	int getEdad() const { return edad; }
	string getNombre() const { return nombre; }

	friend ostream& operator << (ostream & os, Persona const & p);
	friend istream& operator >> (istream & is, Persona & p);

};

ostream& operator << (ostream & os, Persona const & p) {
	os << p.getNombre();
	return os;
}


istream& operator >> (istream & is, Persona & p) {
	int edad;
	string nombre;

	is >> edad;
	getline(is, nombre);
	nombre = nombre.substr(1, nombre.size());

	p.setEdad(edad);
	p.setNombre(nombre);

	return is;
}

template <class T, class funcion>
void filtrar(list<T> & lista, funcion f) {
	typename list<T>::const_iterator it = lista.cbegin();
	typename list<T>::const_iterator itFin = lista.cend();
	
	typename list<T>::const_iterator aux = it;
	while (it != itFin) {
		if (f(*it)) {
			aux = it;
			++it;
			lista.erase(aux);	
		}else{
			++it;
		}
		
	}

}

template <class T>
void mostrar(list<T> const & lista) {
	typename list<T>::const_reverse_iterator rit = lista.crbegin();
	typename list<T>::const_reverse_iterator ritFin = lista.crend();

	while (rit != ritFin) {
		cout << *rit <<endl;
		++rit;
	}
	cout << "---" << endl;
}


void evalua(int const & n) {
	//leer datos
	int min, max;
	list<Persona> lista;
	cin >> min >> max;
	Persona p;
	for (int i = 0; i < n; i++) {
		cin >> p;
		lista.push_front(p);
	}

	auto requisitos = [min, max](Persona p) -> bool {
		if (p.getEdad()<min || p.getEdad() >max) return true;
		return false;
	};

	//filtramos los datos
	filtrar(lista, requisitos);

	//mostramos el resultado

	mostrar(lista);

}


int main() {
	int n;
	cin >> n;
	while (n != 0) {

		evalua(n);

		cin >> n;
	}



	return 0;
}