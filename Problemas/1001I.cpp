// Ejercicio 12 del tema 10
// Implementacion de un consultorio medico
// Se utiliza el tipo de datos HashMap.h
// El listado de los medicos es no ordenado.

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <utility>
#include <list>
#include <iomanip>

#include "Hash.h"
#include "TreeMap.h"

using namespace std;

class Fecha {
	int dia;
	int hora;
	int min;

public:
	Fecha() {}
	Fecha(int const & _dia, int const & _hora, int const & _min) {
		dia = _dia; hora = _hora; min = _min;
	}

	bool operator<(Fecha const & f) const {
		if (this->dia < f.dia) return true;
		else if (this->dia > f.dia) return false;
		//Dias iguales
		if (this->hora < f.hora) return true;
		else if (this->hora > f.hora) return false;
		//Horas iguales
		if (this->min < f.min) return true;
		return false;
	}

	bool operator== (Fecha const & f) const {
		if (this->dia == f.dia && this->hora == f.hora && this->min == f.min) return true;
		return false;
	}

	ostream& operator <<(ostream & o);
	istream& operator >> (istream & i);

	void setDia(int const & _dia) { dia = _dia; }
	void setHora(int const & _hora) { hora = _hora; }
	void setMin(int const & _min) { min = _min; }

	int getDia() const { return dia; }
	int getHora() const { return hora; }
	int getMin() const { return min; }

};

ostream& operator <<(ostream & o, Fecha const & f) {
	o << f.getHora() << ":" << setfill('0') << setw(2) << f.getMin();
	return o;
}

istream& operator >> (istream & i, Fecha & f) {
	int dia, hora, min;
	i >> dia >> hora >> min;
	f.setDia(dia); f.setHora(hora); f.setMin(min);
	return i;
}

typedef string medico;
typedef string paciente;
typedef TreeMap <Fecha, paciente> pacientes;

class consultorio {
	TreeMap< medico,pacientes > tabla;
public:
	void nuevoMedico(medico const& m);
	list<medico> listadoMedicos();
	void pideConsulta(medico const& m, paciente const& p, Fecha const & f);
	paciente const& siguientePaciente(medico const& m);
	void atiendeConsulta(medico const& m);
	void listaPacientes(medico const& m, Fecha const & f);
};

// Añade un medico al consultorio
// Si ya se encuentra no hace nada
void consultorio::nuevoMedico(medico const& m) {
	if (!tabla.contains(m))
        tabla.insert(m, pacientes());
}

// Recorre la tabla mostrando los medicos (en cualquier orden)
list<medico> consultorio::listadoMedicos() {
	list<medico> l;
	TreeMap< medico,pacientes >::ConstIterator it = tabla.cbegin();
	TreeMap< medico,pacientes >::ConstIterator itFin = tabla.cend();
	while (it != itFin) {
		l.push_back(it.key());
		++it;
	}
	return l;
}

// Añade un paciente a la cola de pacientes de un medico
// Si el médico no existe lanza una excepcion
void consultorio::pideConsulta(medico const& m, paciente const& p, Fecha const & f){
	if (tabla.contains(m)){
		if (tabla.at(m).contains(f)) {
			throw invalid_argument("Fecha ocupada");
		}
		/*Sacamos el hashMap<Fecha, paciente> a una variable
		 * para modificarlo*/
		pacientes c = tabla.at(m);
		/*Insertamos el paciente en la fecha correspondiente*/
		c.insert(f, p);
		/*Insertamos el hashMap colaPacientes en su medico*/
		tabla.insert(m, c);
	}
	else throw invalid_argument("Medico no existente");
}

// Obtiene el siguiente paciente de un medico
paciente const& consultorio::siguientePaciente(medico const& m){

	if (tabla.contains(m)) {
		if (tabla.at(m).empty()) {
			throw invalid_argument("No hay pacientes");
		}
		pacientes::ConstIterator it = tabla.at(m).cbegin();
		return tabla.at(m).at(it.key());
	}else {
		throw invalid_argument("Medico no existente");
	}
}


// elimina el primer elemento de la lista de pacientes de un medico
// lanza excepcion si el medico no existe o si la lista de pacientes esta vacia
void consultorio::atiendeConsulta(medico const& m){
	if (tabla.contains(m)){
		if (!tabla.at(m).empty()) {
			pacientes c = tabla.at(m);
			pacientes::ConstIterator it = tabla.at(m).cbegin();
			c.erase(it.key());
			tabla.insert(m,c);
		}
		else throw invalid_argument("No hay pacientes");
	}
	else throw invalid_argument("Medico no existente");
}

// devuelve la lista de pacientes de un medico
void consultorio::listaPacientes(medico const & m, Fecha const & f){
	if(!tabla.contains(m)) throw  invalid_argument("Medico no existente");
	pacientes::ConstIterator it = tabla.at(m).cbegin();
	pacientes::ConstIterator itFin = tabla.at(m).cend();

	while (it != itFin) {
		int dia = it.key().getDia();
		if (dia == f.getDia()) {
			cout << it.value() << " " << it.key() << endl;
		}
		it.next();
	}
	if (tabla.at(m).empty()) cout << endl;
}

// Muestra el contenido de una lista generica
template <class T>
void mostrar(list<T> const& l) {
	typename list<T>::const_iterator it = l.cbegin();
	typename list<T>::const_iterator itFin = l.cend();
	if (it != itFin) {
		cout << *it;
		++it;
	}
	while (it != itFin) {
		cout << ' ' << *it;
		++it;
	}
    
}

bool resolverCaso(){
	consultorio c;
	string nombreMedico;
	string nombrePaciente;
	string nombreOp;
	Fecha fecha;
	int dia;
	int numOp;
	cin >> numOp;
	if (!cin) return false;
	for (int i = 0; i < numOp; ++i) {
		cin >> nombreOp;
		if (nombreOp == "nuevoMedico") {
			cin >> nombreMedico;
			c.nuevoMedico(nombreMedico);
		}
		else if (nombreOp == "pideConsulta") {
			cin >> nombrePaciente >> nombreMedico >> fecha;
			try {
				c.pideConsulta(nombreMedico,nombrePaciente, fecha);
			}
			catch (invalid_argument const& e) {
				cout << e.what() << '\n';
				cout << "---" << endl;
			}
		}
		else if (nombreOp == "siguientePaciente") {
			cin >> nombreMedico;
			try {
				cout << "Siguiente paciente doctor " <<nombreMedico<< '\n';
				cout << c.siguientePaciente(nombreMedico) << '\n';
				cout << "---" << endl;
			}
			catch (invalid_argument const& e) {
				cout << e.what() << '\n';
				cout << "---" << endl;
			}
		}
		else if (nombreOp == "atiendeConsulta") {
			cin >> nombreMedico;
			try {
				c.atiendeConsulta(nombreMedico);
			}
			catch (invalid_argument const& e) {
				cout << e.what() << '\n';
				cout << "---" << endl;
			}
		}
		else if (nombreOp == "listadoMedicos") {
			mostrar(c.listadoMedicos());
			cout << '\n' ;
			cout << "---" << endl;
		}
		else if (nombreOp == "listaPacientes") {
			cin >> nombreMedico >> dia;
			cout << "Doctor " << nombreMedico <<" dia " <<dia << endl;
			c.listaPacientes(nombreMedico, Fecha(dia, 0, 0));
			cout << "---" << endl;
		}
	}
	return true;
}

int main(){

	while (resolverCaso()) {
		cout << "------" << '\n';
	}

	return 0;
}
