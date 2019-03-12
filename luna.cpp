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

	void escribir() { cout << nombre <<endl; }

	friend istream& operator >> (istream & is, Persona & p);

};

istream& operator >> (istream & is, Persona & p){
	int edad;
	string nombre;
	char espacio;

	is >> edad;
	getline(is, nombre);
	nombre = nombre.substr(1, nombre.size());

	p.setEdad(edad);
	p.setNombre(nombre);

	return is;
}


void evalua(int const & n){
	//leer datos
	int min, max;
	DoubleLinkedList<Persona> list = DoubleLinkedList<Persona>();
	cin >> min >> max;
	Persona p;
	for (int i = 0; i < n; i++){
		cin >> p;
		list.push_front(p);
	}

	auto requisitos = [min, max](Persona p) -> bool {
		if (p.getEdad()<min || p.getEdad() >max) return true;
		return false;
	};

	//filtramos los datos
	list.filtrar(requisitos);

	//mostramos el resultado

	list.mostrar();
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