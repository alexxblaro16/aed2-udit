#pragma once
#include <vector>

namespace AEDnames {
	template<typename T>
	//using Nodo = Nodo<T, std::pmr::polymorphic_allocator<T>>;
	class Nodo {
	private:
		T dato;
		Nodo<T>* anterior;
		Nodo<T>* siguiente;

	public:
		Nodo() { anterior = nullptr; siguiente = nullptr; };
		Nodo(const T& _dato, Nodo<T>* _anterior, Nodo<T>* _siguiente)
			: dato(_dato), anterior(_anterior), siguiente(_siguiente)
		{
		}
		//by default inline 
		bool operator==(const Nodo<T>& other) const
		{
			return this->dato == other.dato && this->anterior == other.anterior && this->siguiente == other.siguiente;
		}
		//by default inline
		bool operator!=(const Nodo<T>* other) const
		{
			return this->dato != other->dato || this->anterior != other->anterior || this->siguiente != other->siguiente;
		}


		T getDato();
		bool setDato(T dato);
		void setAnterior(Nodo<T>* anterior);
		Nodo<T>* getAnterior();
		void setSiguiente(Nodo<T>* anterior);
		Nodo<T>* getSiguiente();
	};

	template<typename T>
	//using Nodo = Nodo<T, std::pmr::polymorphic_allocator<T>>;
	class NodoPentagono {
	private:
		T dato;
		NodoPentagono<T>* adj0;
		NodoPentagono<T>* adj1;
		NodoPentagono<T>* adj2;
		NodoPentagono<T>* adj3;


	public:
		NodoPentagono() { adj0 = nullptr; adj1 = nullptr; adj2 = nullptr; adj3 = nullptr;};
		NodoPentagono(T _dato, NodoPentagono<T>* _adj0, NodoPentagono<T>* _adj1, NodoPentagono<T>* _adj2, NodoPentagono<T>* _adj3)
			: dato(_dato), adj0(_adj0), adj1(_adj1), adj2(_adj2), adj3(_adj3)
		{
		}
		//by default inline 
		bool operator==(const NodoPentagono<T>& other) const
		{
			return this->dato == other.dato && this->adj0 == other.adj0 && this->adj1 == other.adj1 && this->adj2 == other.adj2 && this->adj3 == other.adj3;
		}
		//by default inline
		bool operator!=(const NodoPentagono<T>* other) const
		{
			return this->dato != other->dato || this->adj0 != other.adj0 || this->adj1 != other.adj1 || this->adj2 != other.adj2 || this->adj3 != other.adj3;
		}


		T getDato() { return dato; }
		bool setDato(T _dato) { dato = _dato; }
		void setAdjacents(NodoPentagono<T>* adj0, NodoPentagono<T>* adj1, NodoPentagono<T>* adj2, NodoPentagono<T>* adj3);
		NodoPentagono<T>* getAdj0() { return adj0; }
		NodoPentagono<T>* getAdj1() { return adj1; }
		NodoPentagono<T>* getAdj2() { return adj2; }
		NodoPentagono<T>* getAdj3() { return adj3; }
		void setAdj0(NodoPentagono<T>* _adj0) { adj0 = _adj0; }
		void setAdj1(NodoPentagono<T>* _adj1) { adj1 = _adj1; }
		void setAdj2(NodoPentagono<T>* _adj2) { adj2 = _adj2; }
		void setAdj3(NodoPentagono<T>* _adj3) { adj3 = _adj3; }
		
	};

	template<typename T>
	class Lista {
	private:
		Nodo<T>* head;
		Nodo<T>* tail;
		int size;
		Nodo<T>* find(int pos);
	public:
		//Lista() { this.head = new Nodo<T>(); size = 1; }
		Lista() : head(nullptr), tail(nullptr), size(0) {}

		Nodo<T>* getHead() {
			return this->head;
		}
		
		Nodo<T>* getTail() {
			return this->tail;
		}
		
		int getSize() { return size; }
		bool isEmpty() { return size == 0; }
		//setters?
		//setters ? REVISE
		
		bool setHead(Nodo<T>* nodo) {
			if (nodo != nullptr) {
				this->head = nodo;
				return true;
			}
			return false;
		}
		
		bool setTail(Nodo<T>* nodo) {
			if (nodo != nullptr) {
				this->tail = nodo;
				return true;
			}
			return false;
		}

		//manipulation of elements by position
		Nodo<T>* at(int pos);
		bool insertbefore(int pos, Nodo<T>* nodo);
		bool insertafter(int pos, Nodo<T>* nodo);
		bool deleteNode(int pos);

		//manipulation of all elements, need to meet Compare requirements, as the std library expects
		void merge(Lista<T> other);
		void sort();
		void reverse();

	};

	template<typename T>
	class SortedLista {
	private:
		Nodo<T>* head;
		Nodo<T>* tail;
		int size;
		Nodo<T>* find(int pos);
	public:
		//SortedLista() { this.head = new Nodo<T>(); size = 1; }
		SortedLista() : head(nullptr), tail(nullptr), size(0) {}

		Nodo<T>* getHead() { return this->head; }
		Nodo<T>* getTail() { return this->tail;	}
		int getSize() { return size; }
		bool isEmpty() { return size == 0; }
		
		bool setHead(Nodo<T>* nodo) {
			if (nodo != nullptr) {
				this->head = nodo;
				return true;
			}
			return false;
		}

		bool setTail(Nodo<T>* nodo) {
			if (nodo != nullptr) {
				this->tail = nodo;
				return true;
			}
			return false;
		}

		//manipulation of elements by position
		Nodo<T>* at(int pos);
		bool insert(int pos, Nodo<T>* nodo);
		Nodo<T>* search(T dato);
	};


	
}

//need to include the .tpp (template of C++) which has the implementation of the functions, otherwise it will throw the error 'undefined reference' for any fucntion defined with a template 
//remember a template is not actual C++ code, but rather a 'way' of telling the compiler how to generate proper C++ code when an actual type is supplied (specialization of templates)
//this is why we include the 'implementation' in the header, which we will never do with non-template code (only .h and .cpp without any template)
#include "AEDProfeLibI.h"



void bubbleSort(std::vector<int>& arr);
