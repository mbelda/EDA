
#ifndef _DOUBLE_LINKED_LIST_H
#define _DOUBLE_LINKED_LIST_H

#include <iostream>
#include <stdexcept>

template <class T>
class DoubleLinkedList {
public:
	// Constructor sin parámetros
	DoubleLinkedList() : _ini(nullptr) {}
    
	// Constructor copia
	DoubleLinkedList(DoubleLinkedList const& other) {
		_ini = copia(other._ini);
	}
    
	// destructor
	~DoubleLinkedList() {
		libera(_ini);
		_ini = nullptr;
	}
    
	// Operador de asignación
	DoubleLinkedList<T> &operator=(const DoubleLinkedList<T> &other) {
        if (this != &other) {
            libera(_ini);
            _ini = copia(other._ini);
        }
        return *this;
    }
    
	// Operador de comparacion
	bool operator== (DoubleLinkedList<T> const& rhs) const {
		Nodo* aux1 = _ini; Nodo* aux2 = rhs._ini;
		while (aux1 != nullptr && aux2 != nullptr){
			if (aux1->_elem != aux2->_elem) return false;
			aux1 = aux1->_sig;
			aux2 = aux2->_sig;
		}
		return (aux1 == nullptr && aux2 == nullptr);
	}
    
	// Añadir un nodo por el comienzo de la lista
	void push_front(const T &e) {
		Nodo * nuevo = new Nodo(nullptr, e, _ini);
		if (_ini != nullptr) _ini->_ant = nuevo;
        _ini = nuevo;
	}
    
	// Elimina el nodo del comienzo de la lista
	void pop_front() {
		if (_ini == nullptr) throw std::invalid_argument("lista vacia");
		Nodo *aux = _ini;
		_ini = _ini->_sig;
		if (_ini != nullptr) _ini->_ant = nullptr;
		delete aux;
	}

	template <class funcion>
	void filtrar(funcion f){
		Nodo *fin = _ini;

		//buscamos el final
		while (fin->_sig != nullptr){
			fin = fin->_sig;
		}

		//resolvemos
		while (fin != nullptr){
			if (f(fin->_elem)){
				//Si solo hay un elemento
				if (fin->_ant == nullptr && fin->_sig == nullptr) {
					_ini = nullptr;
					delete fin;
					fin = nullptr;
				}

				//Si es el primer elemento pero no el ultimo
				else if (fin->_ant == nullptr) {
					_ini = fin->_sig;
					fin->_sig->_ant = nullptr;
					delete fin;
					fin = nullptr;
				}

				//Si es el ultimo elemento pero no el primero
				else if(fin->_sig == nullptr){
					fin->_ant->_sig = nullptr;
					Nodo *aux = fin;
					fin = fin->_ant;
					delete aux;
				}

				//Si esta en medio
				else {
					fin->_ant->_sig = fin->_sig;
					fin->_sig->_ant = fin->_ant;
					Nodo *aux = fin;
					fin = fin->_ant;
					delete aux;
				}
			}
			else { fin = fin->_ant; }
		}

	}

	void mostrar() {
		Nodo *fin = _ini;
		if (_ini != nullptr) {
			//buscamos el final
			while (fin->_sig != nullptr) {
				fin = fin->_sig;
			}

			while (fin != nullptr) {
				fin->_elem.escribir();
				fin = fin->_ant;
			}
		}
	}
        
private:
	// Clase nodo que almacena internamente el elemento (de tipo T),
	// y un puntero al nodo siguiente.
	class Nodo {
    public:
		Nodo() : _sig(nullptr), _ant(nullptr) {}
		Nodo(const T &elem) : _elem(elem), _sig(nullptr), _ant(nullptr) {}
		Nodo(Nodo* ant, const T &elem, Nodo *sig) :
        _elem(elem), _sig(sig), _ant(ant) {}
        
		T _elem;
		Nodo* _sig;
		Nodo* _ant;
	};
    
	// Puntero al primer elemento
	Nodo *_ini;
    
	// libera todos los nodos de la lista
    void libera(Nodo *ini) {
		while (ini != nullptr) {
			Nodo *aux = ini;
			ini = ini->_sig;
			delete aux;
		}
	}
    
    // Copia el parámetro en la lista.
    // La lista debe estar vacia.
	Nodo* copia(Nodo* other) {
		if (other == nullptr) return nullptr;
		else if (other->_sig == nullptr) { // Un solo elemento
			Nodo* nuevo = new Nodo(other->_elem);
			return nuevo;
		}
		else {
			Nodo* aux = copia(other->_sig);
			Nodo* nuevo = new Nodo(nullptr, other->_elem, aux);
			aux->_ant = nuevo;
			aux = nuevo;
			return aux;
		}
	}
    
};

#endif // _DOUBLE_LINKED_LIST_H

