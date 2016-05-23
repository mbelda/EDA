#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <utility>
#include <list>
#include "TreeMap.h"
#include "HashMap.h"
using namespace std;


typedef string medico;
typedef string paciente;

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
	o << f.getHora() << ":" << f.getMin();
	return o;
}

istream& operator >> (istream & i, Fecha & f) {
	int dia, hora, min;
	i >> dia >> hora >> min;
	f.setDia(dia); f.setHora(hora); f.setMin(min);
	return i;
}

typedef TreeMap<Fecha, paciente> pacientes;

class consultorio {
	HashMap< medico, pacientes > tabla;
public:
	void nuevoMedico(medico const& m);
	list<medico> listadoMedicos();
	void pideConsulta(medico const& m, paciente const& p, Fecha const & f);
	paciente const& siguientePaciente(medico const& m);
	void atiendeConsulta(medico const& m);
	pacientes const& listaPacientes(medico const& m, Fecha const & f);
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
	HashMap< medico, pacientes >::ConstIterator it = tabla.cbegin();
	HashMap< medico, pacientes >::ConstIterator itFin = tabla.cend();
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
	if (tabla.contains(m)){
		cout << "Siguiente Paciente doctor " << m << endl;
		if (tabla.at(m).empty()) {
		throw invalid_argument("No hay pacientes");
		}
		else{
			pacientes :: ConstIterator it = tabla.at(m).cbegin();
			return it.value();
		}
	}
	else throw invalid_argument("Medico no existente");
}

// elimina el primer elemento de la lista de pacientes de un medico
// lanza excepcion si el medico no existe o si la lista de pacientes esta vacia
void consultorio::atiendeConsulta(medico const& m){
	if (tabla.contains(m)){
		pacientes l = tabla.at(m);
		if (l.empty()) {
		throw invalid_argument("No hay pacientes");
		}
		else{
			pacientes :: ConstIterator it = l.cbegin();
			l.erase(it.key());
			tabla.insert(m, l);
		}
	}
	else throw invalid_argument("Medico no existente");
}

// devuelve la lista de pacientes de un medico
void consultorio::listaPacientes(medico const & m, int dia, list<Cita> & lista){
	if (tabla.contains(m)){
		pacientes :: ConstIterator it = tabla.at(m).cbegin();
		pacientes :: ConstIterator itFin = tabla.at(m).cend();
	cout << "Doctor " << m << " dia " << dia << endl; 
	while(it!=itFin){
		if(dia == it.key().getDia()) {
			Cita elemento = Cita(it.value(), it.key());
			lista.push_back(elemento);
		}
		else{}
		it.next();
	}
	}
	else throw invalid_argument("Medico no existente");
	
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
		cout << endl << *it;
		++it;
	}

}

bool resolverCaso(){
	consultorio c;
	string nombreMedico;
	string nombrePaciente;
	string nombreOp;
	Fecha fecha(0, 0, 0);
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
			cin >> nombrePaciente >> nombreMedico;
			cin >> fecha;
			try {
				c.pideConsulta(nombreMedico, nombrePaciente, fecha);
			}
			catch (invalid_argument const& e) {
				cout << e.what() << '\n';
				cout << "---" << '\n';
			}
		}
		else if (nombreOp == "siguientePaciente") {
			cin >> nombreMedico;
			try {
				cout << c.siguientePaciente(nombreMedico) << '\n';
				cout << "---" << '\n';
			}
			catch (invalid_argument const& e) {
				cout << e.what() << '\n';
				cout << "---" << '\n';
			}
			catch (out_of_range const& e) {
				cout << e.what() << '\n';
				cout << "---" << '\n';
			}
		}
		else if (nombreOp == "atiendeConsulta") {
			cin >> nombreMedico;
			try {
				c.atiendeConsulta(nombreMedico);
			}
			catch (invalid_argument const& e) {
				cout << e.what() << '\n';
				cout << "---" << '\n';
			}
			catch (out_of_range const& e) {
				cout << e.what() << '\n';
				cout << "---" << '\n';
			}
		}
		else if (nombreOp == "listadoMedicos") {
			mostrar(c.listadoMedicos()); cout << '\n';
			cout << "---" << '\n';
		}
		else if (nombreOp == "listaPacientes") {
			cin >> nombreMedico;
			int dia;
			cin >> dia;
			list<Cita> lista;
			c.listaPacientes(nombreMedico, dia, lista);
			mostrar(lista); cout << '\n';
			cout << "---" << '\n';
		}
	}
	return true;
}

int main(){
	while (resolverCaso()){
	cout << "------" << '\n';
	}
	return 0;
}
