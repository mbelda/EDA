#include <iostream>
#include <string>
#include "doubleLinkedList.h"
using namespace std;

class Persona{
	string nombre;
	int edad;

public:

	void setEdad(int const & ed){ edad = ed; }
	void setNombre(string const & n){ nombre = n; }

	int getEdad() const{ return edad; }
	string getNombre() const { return nombre; }

	friend istream& operator >> (istream & is, Persona & p);
	friend ostream& operator << (ostream & os, Persona & p);

};

istream& operator >> (istream & is, Persona & p){
	int edad;
	string nombre;

	is >> edad;
	getline(is, nombre);

	p.setEdad(edad);
	p.setNombre(nombre);

	return is;
}

ostream& operator << (ostream & os, const Persona & p) {
	os << p.getNombre();
	return os;
}

void evalua(int const & n){
	//leer datos
	int min, max;
	DoubleLinkedList<Persona> list = DoubleLinkedList<Persona>();
	cin >> min >> max;
	for (int i = 0; i < n; i++){
		Persona p;
		cin >> p;
		list.push_front(p);
	}

	//filtramos los datos
	list.resuelve(min, max);

	//mostramos el resultado
	for (int i = 0; i < list.size(); i++){
		cout << list.at(i) << endl;
	}
	cout << "---" << endl;


}


int main(){
	int n;
	cin >> n;
	while (n != 0){

		evalua(n);

		cin >> n;
	}



	return 0;
}