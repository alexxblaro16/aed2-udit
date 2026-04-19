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
		// Es raiz si no tiene padre
		return this->parent == nullptr;
	}
	//these must work even if 'this' is not the root of the tree
	template<typename T>
	unsigned int NodoTree<T>::getUpHeight() {
		// Distancia (numero de aristas) entre este nodo y la raiz
		unsigned int h = 0;
		NodoTree<T>* cur = this->parent;
		while (cur != nullptr) {
			++h;
			cur = cur->parent;
		}
		return h;
	}
	template<typename T>
	unsigned int NodoTree<T>::getDownHeight() {
		// Distancia hasta la hoja mas lejana en su subarbol
		// Caso base: hoja -> 0
		if (this->left == nullptr && this->right == nullptr) return 0;
		unsigned int hl = 0, hr = 0;
		if (this->left) hl = 1 + this->left->getDownHeight();
		if (this->right) hr = 1 + this->right->getDownHeight();
		return hl > hr ? hl : hr;
	}
	template<typename T>
	NodoTree<T>* NodoTree<T>::getleftleaf() {
		// Hoja mas a la izquierda del subarbol
		NodoTree<T>* cur = this;
		while (cur->left != nullptr || cur->right != nullptr) {
			cur = cur->left != nullptr ? cur->left : cur->right;
		}
		return cur;
	}

	template<typename T>
	NodoTree<T>* NodoTree<T>::getrightleaf() {
		// Hoja mas a la derecha del subarbol
		NodoTree<T>* cur = this;
		while (cur->left != nullptr || cur->right != nullptr) {
			cur = cur->right != nullptr ? cur->right : cur->left;
		}
		return cur;
	}
	template<typename T>
	NodoTree<T>* NodoTree<T>::getRoot() {
		// Sube por la cadena de padres hasta encontrar la raiz
		NodoTree<T>* cur = this;
		while (cur->parent != nullptr) cur = cur->parent;
		return cur;
	}

	//AEDTree
	template<typename T>
	unsigned int AEDTree<T>::getHeight() {
		if (root == nullptr) return 0;
		return root->getDownHeight();
	}

	template<typename T>
	NodoTree<T>* AEDTree<T>::getleftleaf() {
		return root ? root->getleftleaf() : nullptr;
	}

	template<typename T>
	NodoTree<T>* AEDTree<T>::getrightleaf() {
		return root ? root->getrightleaf() : nullptr;
	}

	template<typename T>
	NodoTree<T>* AEDTree<T>::getRoot() {
		return root;
	}

	//must walk through the children from right to left and ignore the leaves
	template<typename T>
	std::vector<NodoTree<T>*> AEDTree<T>::breadthSpecial() {
		// BFS por niveles: hijos visitados de derecha a izquierda, hojas ignoradas (no se anyaden al resultado)
		std::vector<NodoTree<T>*> res;
		if (root == nullptr) return res;
		std::queue<NodoTree<T>*> q;
		q.push(root);
		while (!q.empty()) {
			NodoTree<T>* cur = q.front(); q.pop();
			bool esHoja = (cur->left == nullptr && cur->right == nullptr);
			if (!esHoja) res.push_back(cur);
			// Encolamos primero el derecho para que se procese antes (derecha->izquierda)
			if (cur->right) q.push(cur->right);
			if (cur->left)  q.push(cur->left);
		}
		return res;
	}
	template<typename T>
	void depthSpecialaux(NodoTree<T>* current, std::vector<NodoTree<T>*>* res) {
		if (current == nullptr) return;
		bool esHoja = (current->left == nullptr && current->right == nullptr);
		if (!esHoja) res->push_back(current);
		// Preorden derecha->izquierda: visitamos derecho antes que izquierdo
		if (current->right) depthSpecialaux(current->right, res);
		if (current->left)  depthSpecialaux(current->left, res);
	}

	//must walk through the children from right to left and ignore the leaves
	template<typename T>
	std::vector<NodoTree<T>*> AEDTree<T>::depthSpecial() {
		std::vector<NodoTree<T>*> res;
		depthSpecialaux(root, &res);
		return res;
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

	//Heap (max-heap por prio: pop devuelve el de mayor prioridad)
	template <typename T>
	void Heap<T>::insert(T dato, int prio) {
		// Insertamos al final y subimos el elemento hasta su posicion correcta
		NodoHeap<T> n;
		n.dato = dato;
		n.prio = prio;
		arr.push_back(n);
		size++;
		upHeap(static_cast<int>(arr.size()) - 1);
	}
	template <typename T>
	NodoHeap<T> Heap<T>::pop() {
		// Sacamos la raiz (mayor prio). Movemos el ultimo a la raiz y bajamos.
		NodoHeap<T> top = arr[0];
		int last = static_cast<int>(arr.size()) - 1;
		arr[0] = arr[last];
		arr.pop_back();
		size--;
		if (!arr.empty()) downHeap(0);
		return top;
	}
	template <typename T>
	void Heap<T>::upHeap(int i) {
		while (i > 0) {
			int parent = (i - 1) / 2;
			// Si el hijo es mayor que el padre, intercambiamos
			if (arr[parent] < arr[i]) {
				std::swap(arr[parent], arr[i]);
				i = parent;
			} else {
				break;
			}
		}
	}
	template <typename T>
	void Heap<T>::downHeap(int i) {
		int n = static_cast<int>(arr.size());
		while (true) {
			int left = 2 * i + 1;
			int right = 2 * i + 2;
			int largest = i;
			// Buscamos el mayor entre i y sus dos hijos (si existen)
			if (left < n && arr[largest] < arr[left]) largest = left;
			if (right < n && arr[largest] < arr[right]) largest = right;
			if (largest == i) break;
			std::swap(arr[i], arr[largest]);
			i = largest;
		}
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