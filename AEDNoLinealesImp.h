#include "AEDNoLineales.h"
#include <algorithm>
#include <queue>
#include <set>
#include <unordered_set>
#include <cstdint>

namespace AEDnames {

	//NodoTree
	template<typename T>
	bool NodoTree<T>::isRoot() {
		
	}
	//these must work even if 'this' is not the root of the tree
	template<typename T>
	unsigned int NodoTree<T>::getUpHeight() {
		
	}
	template<typename T>
	unsigned int NodoTree<T>::getDownHeight() {
		
	}
	template<typename T>
	NodoTree<T>* NodoTree<T>::getleftleaf() {
		
	}

	template<typename T>
	NodoTree<T>* NodoTree<T>::getrightleaf() {
		
	}
	template<typename T>
	NodoTree<T>* NodoTree<T>::getRoot() {
		
	}

	//AEDTree
	template<typename T>
	unsigned int AEDTree<T>::getHeight() {
		
	}

	//must walk through the children from right to left and ignore the leaves
	template<typename T>
	std::vector<NodoTree<T>*> AEDTree<T>::breadthSpecial() {
		
	}
	template<typename T>
	void depthSpecialaux(NodoTree<T>* current, std::vector<NodoTree<T>*>* res) {
		
	}

	//must walk through the children from right to left and ignore the leaves
	template<typename T>
	std::vector<NodoTree<T>*> AEDTree<T>::depthSpecial() {
		
	}

	//Graph

	template<typename T>
	NodoGraph<T>* NodoGraph<T>::search(T dato) {
		
	}

	// Auxiliar BFS que toma un nodo de grafo y construye un �rbol (copia)
	template<typename T>
	NodoGraph<T>* spanningTreeAux(NodoGraph<T>* start) {
		
	}

	template<typename T>
	NodoGraph<T>* NodoGraph<T>::spanningTree() {
		
	}

	template<typename T>
	std::vector<NodoGraph<T>*> AEDnames::NodoGraph<T>::findMinPath(NodoGraph<T>* init, NodoGraph<T>* dest) {
		
	}

	//Heap
	template <typename T>
	void Heap<T>::insert(T dato, int prio) {
		
	}
	template <typename T>
	NodoHeap<T> Heap<T>::pop() {
		
	}
	template <typename T>
	void Heap<T>::upHeap(int i) {

	}
	template <typename T>
	void Heap<T>::downHeap(int i) {

	}



	//AEDMap
	template<typename T>
	int AEDMap<T>::badHash(T* value) {
		// Cogemos los 16 bits bajos de la direccion como hash: provoca colisiones a proposito.
		// Usamos uintptr_t para que el reinterpret_cast sea legal (puntero -> entero suficientemente grande).
		if (value == nullptr) return 0;
		auto p = reinterpret_cast<std::uintptr_t>(value);
		return static_cast<int>(p & 0xFFFF);
	}
	template<typename T>
	int AEDMap<T>::hashToIndex(int hash) {
		

	}
	template<typename T>
	bool AEDMap<T>::insert(T* value) {
		
	}
	template<typename T>
	bool AEDMap<T>::remove(T* value) {
		
	}
	//don't know why this returns int
	template<typename T>
	int AEDMap<T>::search(T* value) {
		
	}
	template<typename T>
	bool AEDMap<T>::contains(T* value) {
		
	}
	template<typename T>
	bool AEDMap<T>::isEmpty() {
		
	}
	template<typename T>
	int AEDMap<T>::size() {
		
	}
}