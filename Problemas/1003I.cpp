// Problema 1 del tema 11
// Implementacion de un sistema de venta de libros por internet

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <map>
#include <utility>
#include <list>
#include "TreeMap.h"
#include "HashMap.h"
using namespace std;

struct infoLibro {
	int numEjemplares;
	int numVendidos;
};

typedef string libro;


typedef HashMap<libro, infoLibro> ventaLibro;
typedef TreeMap<int, list<libro>> librosVendidos;

class VentaLibros {
	ventaLibro tablaLibros;
	librosVendidos arbolLibros;
public:
	//Complejidad constante. 	
	void nuevoLibro(libro const& titulo, int ejemplares) {
		if (tablaLibros.contains(titulo)) {
			tablaLibros[titulo].numEjemplares += ejemplares;
		}
		else {
			infoLibro info;
			info.numEjemplares = ejemplares;
			info.numVendidos = 0;
			tablaLibros.insert(titulo, info);
		}
	}
	
	//Complejidad lineal, debido a la funcion remove de la STL o al push_back 
	void comprar(libro const& titulo) {
		if(!tablaLibros.contains(titulo)) throw invalid_argument("Libro no existente");
		if(tablaLibros.at(titulo).numEjemplares == 0) throw out_of_range("No hay ejemplares");

		int vendidos = tablaLibros.at(titulo).numVendidos;
 
		//por lo tanto quitamos un ejemplar y añadimos 1 a los vendidos.
		tablaLibros[titulo].numEjemplares--;
		tablaLibros[titulo].numVendidos++;

		//Despues comprobamos si se ha vendido alguna vez con la variable vendidos que es la varible antes de añadirle 1.
		//Y en tal caso lo borramos de la lista para añadirselo a la lista con un numVendidos mas que la anterior.
		if (vendidos != 0) {
			arbolLibros[vendidos].remove(titulo);
		}
		//Comprbamos si la lista ya existe en el arbol, si existe le añadimos este libro en la primera posición
		if (arbolLibros.contains(tablaLibros[titulo].numVendidos)) { //Comprbamos si la lista ya existe en el arbol.
			arbolLibros[tablaLibros[titulo].numVendidos].push_back(titulo);
			//El libro se añade al final de la lista para que esten ordenados en la lista de menor(libro vendido mas "antiguo")
			//a mayor(libro vendido mas "reciente").
		}
		//Sino se crea y se añade por primera vez la lista al arbol.
		else {
			list<libro> lista;
			lista.push_back(titulo);
			arbolLibros.insert(tablaLibros[titulo].numVendidos, lista);
		}

	}
	
	//Complejidad constante acceder al dato de una tabla es constante.
	bool estaLibro(libro const& titulo) const {
		return tablaLibros.contains(titulo);
	}
	
	//Complejidad lineal o constante dependiendo de si el libro ha sido vendido o no. 
	void elimLibro(libro const& titulo) {
		if (tablaLibros.contains(titulo)) { //Comprbamos que el libro existe.
			int vendidos = tablaLibros.at(titulo).numVendidos; //Si se ha vendido alguna vez hay que quitarlo del arbol.
			if (vendidos != 0) {
				arbolLibros[vendidos].remove(titulo);
			}
			//Posteriormente lo eliminamos de la tabla/sistema
			tablaLibros.erase(titulo);
		}
	}
	
	//Complejidad constante acceder al dato de una tabla es constante.
	int numEjemplares(libro const& titulo) const {
		if (tablaLibros.contains(titulo)) {
			return tablaLibros.at(titulo).numEjemplares;
		}
		else {
			throw invalid_argument("Libro no existente");
		}
	}
	
	//Complejidad lineal sobre el numero de elementos ya que el iterador del TreeMap es lineal con respecto al numero de ventas y el numero de libros en las listas.
	list<libro> top10() const {
		//Iteradores del arbol
		librosVendidos::ConstIterator it = arbolLibros.cbegin();
		librosVendidos::ConstIterator itFin = arbolLibros.cend();
		list<libro> listRetorno;
		while (it != itFin) {//Bucle para recorrer el arbol de busqueda entero
			list<libro> listaActual = it.value();
			//Iteradores de la lista correspondiente al respectivo nodo it del arbol
			list<libro> ::const_iterator itListaActual = listaActual.cbegin();
			list<libro> ::const_iterator itFinListaActual = listaActual.cend();

			while (itListaActual != itFinListaActual) {//Bucle para recorrer la lista del nodo correspondiente del arbol
				listRetorno.push_front(*itListaActual);
				if (listRetorno.size()>10) { //Asi mantenemos que se mantengan solo los 10 libros mas vendidos y los mas recientes.
					listRetorno.pop_back();
				}
				++itListaActual;
			}
			++it;
		}
		return listRetorno;
	}
};

// Muestra el contenido de una lista
template <class T>
void mostrar(list<T> const& l) {
	typename list<T>::const_iterator it = l.cbegin();
	typename list<T>::const_iterator itFin = l.cend();
	while (it != itFin) {
		cout << *it << '\n';
		++it;
	}

}

bool resolverCaso() {
	VentaLibros c;
	libro tituloLibro;
	int numUnidades;
	string nombreOp;
	int numOp;
	cin >> numOp;
	if (!cin) return false;
	for (int i = 0; i < numOp; ++i) {
		cin >> nombreOp;
		char aux;
		cin.get(aux); // lee el blanco despues del nombre de la operacion
		if (nombreOp == "nuevoLibro") {
			cin >> numUnidades;
			char aux;
			cin.get(aux); // lectura del blanco entre las unidades y el titulo
			getline(cin, tituloLibro);
			c.nuevoLibro(tituloLibro, numUnidades);
		}
		else if (nombreOp == "comprar") {
			getline(cin, tituloLibro);
			try {
				c.comprar(tituloLibro);
			}
			catch (out_of_range const& e) {  // No hay ejemplares
				cout << e.what() << '\n';
				cout << "---\n";
			}
			catch (invalid_argument const& e) {  //Libro no existente
				cout << e.what() << '\n';
				cout << "---\n";
			}
		}
		else if (nombreOp == "estaLibro") {
			getline(cin, tituloLibro);
			if (c.estaLibro(tituloLibro)) {
				cout << "El libro " << tituloLibro;
				cout << " esta en el sistema\n";
			}
			else {
				cout << "No existe el libro " << tituloLibro;
				cout << " en el sistema\n";
			}
			cout << "---\n";
		}
		else if (nombreOp == "elimLibro") {
			getline(cin, tituloLibro);
			c.elimLibro(tituloLibro);
		}
		else if (nombreOp == "numEjemplares") {
			getline(cin, tituloLibro);
			if (c.estaLibro(tituloLibro)) {
				cout << "Existen " << c.numEjemplares(tituloLibro);
				cout << " ejemplares del libro " << tituloLibro << '\n';
			}
			else {
				cout << "No existe el libro " << tituloLibro;
				cout << " en el sistema\n";
			}
			cout << "---\n";
		}
		else if (nombreOp == "top10") {
			mostrar(c.top10());
			cout << "---\n";
		}
	}
	return true;

}

int main() {
	while (resolverCaso()) {
		cout << "------\n";
	}
	return 0;
}
