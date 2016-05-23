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

struct infoLibro{
	int numEjemplares;
	float precio;
};

typedef string libro;

typedef HashMap<libro, infoLibro> ventaLibro;
typedef TreeMap<int, list<libro>> librosVendidos;

class VentaLibros{
	ventaLibro tablaLibros;
public:
	//Complejidad constante. 	
	void nuevoLibro(libro const& titulo, int ejemplares, float precio) {
		if (this->tablaLibros.contains(titulo)){
			this->tablaLibros[titulo].numEjemplares += ejemplares;
		}
		else{
			infoLibro info;
			info.numEjemplares = ejemplares;
			info.precio = precio;
			this->tablaLibros.insert(titulo,info);
		}
	}
	//Complejidad lineal, debido a la funcion remove de la STL o al push_back 
	void comprar(int num){
		libro titulo;
		float precioTotal=0;
		getline(cin, titulo);
		for(int i=0; i < num; i++){
			getline(cin, titulo);
			if (this->tablaLibros.contains(titulo)){ //Comprbamos que el libro existe.
				if (this->tablaLibros.at(titulo).numEjemplares != 0){//Primero comprobamos tiene ejemplares
					this->tablaLibros[titulo].numEjemplares--;
					precioTotal += this->tablaLibros.at(titulo).precio;
				}
				else{
					throw out_of_range("No hay ejemplares");
				}
			}
			else{
				throw invalid_argument("Libro no existente");
 			}
		}
		cout << "Precio Total " << precioTotal << endl << "---" << endl;
	}
};


bool resolverCaso(){
	VentaLibros c;
	libro tituloLibro;
	int numUnidades;
	int numLibros;
	float precio;
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
			cin >> precio;
			char aux;
			cin.get(aux); // lectura del blanco entre las unidades y el titulo
			getline(cin, tituloLibro);
			c.nuevoLibro(tituloLibro, numUnidades, precio);
		}
		else if (nombreOp == "comprar") {
			cin >> numLibros;
			try {
				c.comprar(numLibros);
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
	}
	return true;

}

int main(){
	while (resolverCaso()){ 
		cout << "------\n"; 
	}
	return 0;
}
