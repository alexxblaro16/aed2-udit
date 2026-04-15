#pragma once

#include "AEDProfeLib.h"

namespace AEDnames {
	//Nodo
	template<class T>
	T Nodo<T>::getDato() {
		return this->dato;
	}

	template<class T>
	bool Nodo<T>::setDato(T dato) {
		this->dato = dato;
		return true;
	}
	template<class T>
	void Nodo<T>::setAnterior(Nodo<T>* anterior) {
		// Permitimos nullptr (necesario para marcar el extremo de la lista)
		this->anterior = anterior;
	}
	template<class T>
	Nodo<T>* Nodo<T>::getAnterior() {
		return this->anterior;
	}
	template<class T>
	void Nodo<T>::setSiguiente(Nodo<T>* siguiente) {
		// Permitimos nullptr (necesario para marcar el extremo de la lista)
		this->siguiente = siguiente;
	}
	template<class T>
	Nodo<T>* Nodo<T>::getSiguiente() {
		return this->siguiente;
	}


	//NodoPentagono
	template<class T>
	void NodoPentagono<T>::setAdjacents(NodoPentagono<T>* adj0, NodoPentagono<T>* adj1, NodoPentagono<T>* adj2, NodoPentagono<T>* adj3) {
		this->setAdj0(adj0);
		this->setAdj1(adj1);
		this->setAdj2(adj2);
		this->setAdj3(adj3);
	}
	
	//Lista
	//not implemented!
	template<typename T>
	Nodo<T>* Lista<T>::find(int pos) {
		Nodo<T>* current = this->head;
		for (int i = 0; i < pos && i < this->size; i++) {
			current = current->getSiguiente();
		}
		return current;
	}
	template<typename T>
	Nodo<T>* Lista<T>::at(int pos) {
		return find(pos);
	}
	template<typename T>
	bool Lista<T>::insertbefore(int pos, Nodo<T>* nodo) {
		Nodo<T>* right = find(pos);
		Nodo<T>* left = nullptr;
		if (right != nullptr)
			left = right->getAnterior();
		//change pointers of inserted node
		nodo->setSiguiente(right);
		nodo->setAnterior(left);
		//change pointers of right node
		if (right != nullptr)
			right->setAnterior(nodo);
		else
			tail = nodo;
		//change pointers of left node
		if (left != nullptr) {
			left->setSiguiente(nodo);
		}
		else
			head = nodo;
		size++;
		return true;
	}
	template<typename T>
	bool Lista<T>::insertafter(int pos, Nodo<T>* nodo) {
		Nodo<T>* left = find(pos);
		Nodo<T>* right = nullptr;
		if (left != nullptr)
			right = left->getSiguiente();
		//change pointers of inserted node
		nodo->setSiguiente(right);
		nodo->setAnterior(left);
		//change pointers of right node
		if (right != nullptr)
			right->setAnterior(nodo);
		else
			tail = nodo;
		//change pointers of left node
		if (left != nullptr)
			left->setSiguiente(nodo);
		else
			head = nodo;

		size++;
		return true;
	}

	template<typename T>
	bool Lista<T>::deleteNode(int pos) {
		Nodo<T>* nodo = find(pos);
		if (nodo == nullptr) return false;
		Nodo<T>* left = nodo->getAnterior();
		Nodo<T>* right = nodo->getSiguiente();
		// Si borramos la cabeza o la cola, hay que reasignarlas
		if (left != nullptr) left->setSiguiente(right);
		else head = right;
		if (right != nullptr) right->setAnterior(left);
		else tail = left;
		delete nodo;
		size--;
		return true;
	}

	//manipulation of all elements, need to meet Compare requirements, as the std library expects
	template<typename T>
	void Lista<T>::merge(Lista<T> other) {
	
	}

	template<typename T>
	void Lista<T>::sort() {
	
	}

	template<typename T>
	void Lista<T>::reverse() {
		// Recorremos la lista intercambiando anterior y siguiente en cada nodo
		Nodo<T>* curr = head;
		Nodo<T>* prev = nullptr;
		while (curr != nullptr) {
			Nodo<T>* nextOrig = curr->getSiguiente();
			curr->setSiguiente(prev);
			curr->setAnterior(nextOrig);
			prev = curr;
			curr = nextOrig;
		}
		// Intercambiamos head y tail
		Nodo<T>* tmp = head;
		head = tail;
		tail = tmp;
	}

	template<typename T>
	Nodo<T>* SortedLista<T>::find(int pos) {
		Nodo<T>* current = this->head;
		for (int i = 0; i < pos && i < this->size; i++) {
			current = current->getSiguiente();
		}
		return current;
	}

	template<typename T>
	Nodo<T>* SortedLista<T>::at(int pos) {
		return find(pos);
	}
	
	template<typename T>
	bool SortedLista<T>::insert(int pos, Nodo<T>* nodo) {
		return false;
	}
	template<typename T>
	Nodo<T>* SortedLista<T>::search(T dato) {
		return nullptr;
	}
	
}