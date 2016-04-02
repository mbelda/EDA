#ifndef _SINGLY_LINKED_LIST_H
#define _SINGLY_LINKED_LIST_H

#include <iostream>
#include <stdexcept>
using namespace std;


template <class T>
class SinglyLinkedList {

	/**
	Clase nodo que almacena internamente el elemento (de tipo T),
	y un puntero al nodo siguiente.
	*/
	class Nodo {
	public:
		T _elem;
		Nodo *_sig;

		Nodo() : _sig(nullptr) {}
		Nodo(const T &elem) : _elem(elem), _sig(nullptr) {}
		Nodo(const T &elem, Nodo *sig) :
			_elem(elem), _sig(sig) {}
	
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
		else if (other->_sig == nullptr) {
			Nodo* nuevo = new Nodo(other->_elem);
			return nuevo;
		}
		else {
			Nodo* aux = copia(other->_sig);
			Nodo* nuevo = new Nodo(other->_elem, aux);
			aux = nuevo;
			return aux;
		}
	}


public:
	// Constructor sin parámetros
	SinglyLinkedList() : _ini(nullptr) {}

	// Constructor copia
	SinglyLinkedList(SinglyLinkedList const& other) {
		_ini = copia(other._ini);
	}

	// destructor
	~SinglyLinkedList() {
		libera(_ini);
		_ini = nullptr;
	}

	// Operador de asignación
	SinglyLinkedList<T> &operator=(SinglyLinkedList<T> const& other) {
		if (this != &other) {
			libera(_ini);
			_ini = copia(other._ini);
		}
		return *this;
	}

	// Operador de comparacion
	bool operator== (SinglyLinkedList<T> const& rhs) const {
		Nodo* aux1 = _ini; Nodo* aux2 = rhs._ini;
		while (aux1 != nullptr && aux2 != nullptr && aux1->_elem == aux2->_elem) {
			aux1 = aux1->_sig;
			aux2 = aux2->_sig;
		}
		if (aux1 == nullptr && aux2 == nullptr) return true;
		else return false;
	}

	// Añadir un nodo por el comienzo de la lista
	void push_front(T const& e) {
		Nodo * nuevo = new Nodo(e, _ini);
		_ini = nuevo;
	}

	// Elimina el nodo del comienzo de la lista
	void pop_front() {
		if (_ini == nullptr) throw std::invalid_argument("lista vacia");
		Nodo *aux = _ini;
		_ini = _ini->_sig;
		delete aux;
	}

	void invertir() {
		Nodo * aux;
		Nodo * resultado = nullptr;

		while (_ini != nullptr) {
			aux = _ini;
			_ini = _ini->_sig;
			aux->_sig = resultado;
			resultado = aux;
		}

		_ini = resultado;
	}

	void duplicate() {
		Nodo * copia = _ini;
		_ini = nullptr;
		while (copia != nullptr) {
			for (int i = 0; i < 2; i++) {
				push_front(copia->_elem);
			}
			copia = copia->_sig;
		}
		
		invertir();
	}

	void mostrar() {
		Nodo* aux = _ini;
		if (_ini != nullptr) {
			cout << _ini->_elem;
			_ini = _ini->_sig;
			while (_ini != nullptr) {
				cout <<" " << _ini->_elem;
				_ini = _ini->_sig;
			}
			_ini = aux;
		}
	}

	void creciente() {
		Nodo *auxAnt = _ini;
		Nodo *aux = _ini->_sig;
		while (aux != nullptr) {
			if (aux->_elem < auxAnt->_elem) {
				auxAnt->_sig = aux->_sig;
				delete aux;
				aux = auxAnt->_sig;
			}
			else {
				auxAnt = aux;
				aux = aux->_sig;
			}
		}
	}

private:

	

};

#endif // _SINGLY_LINKED_LIST_H

#pragma once
