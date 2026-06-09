#pragma once
#include "AEDNoLineales.h"
#include <algorithm>
#include <queue>
#include <cstdint>

namespace AEDnames {

	// Busca un nodo dentro de un vector de nodos y devuelve su indice, o -1 si no esta.
	// Lo usamos en los algoritmos de grafo para no depender de std::map ni std::set.
	template<typename T>
	int indiceDe(const std::vector<NodoGraph<T>*>& v, NodoGraph<T>* n) {
		for (size_t i = 0; i < v.size(); ++i) {
			if (v[i] == n) return static_cast<int>(i);
		}
		return -1;
	}

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
		// BFS desde 'this'. Si 'this' coincide ya devolvemos this. Si no, recorremos adyacencias.
		// Guardamos los nodos visitados en un vector (sin std::set ni std::unordered_set).
		if (this->dato == dato) return this;
		std::vector<NodoGraph<T>*> vis;
		std::queue<NodoGraph<T>*> q;
		vis.push_back(this);
		q.push(this);
		while (!q.empty()) {
			NodoGraph<T>* cur = q.front(); q.pop();
			for (auto& adjPair : cur->adjs) {
				NodoGraph<T>* adj = adjPair.first;
				if (indiceDe(vis, adj) >= 0) continue;
				if (adj->dato == dato) return adj;
				vis.push_back(adj);
				q.push(adj);
			}
		}
		return nullptr;
	}

	// Auxiliar BFS que toma un nodo de grafo y construye un arbol (copia)
	template<typename T>
	NodoGraph<T>* spanningTreeAux(NodoGraph<T>* start) {
		// Copia profunda BFS: cada nodo del grafo original tiene una copia 1:1.
		// Las aristas que cerrarian ciclo se descartan (asi sale un arbol).
		// Mantenemos dos vectores paralelos: origs[i] del grafo original y su copia copias[i]
		// (en vez de un std::unordered_map original->copia).
		std::vector<NodoGraph<T>*> origs;
		std::vector<NodoGraph<T>*> copias;
		NodoGraph<T>* copyRoot = new NodoGraph<T>(start->dato);
		origs.push_back(start);
		copias.push_back(copyRoot);
		std::queue<NodoGraph<T>*> q;
		q.push(start);
		while (!q.empty()) {
			NodoGraph<T>* orig = q.front(); q.pop();
			NodoGraph<T>* copy = copias[static_cast<size_t>(indiceDe(origs, orig))];
			for (auto& adjPair : orig->adjs) {
				NodoGraph<T>* adj = adjPair.first;
				unsigned int w = adjPair.second;
				// Solo creamos la copia y conectamos si no estaba visitada (asi evitamos ciclos)
				if (indiceDe(origs, adj) < 0) {
					NodoGraph<T>* copyAdj = new NodoGraph<T>(adj->dato);
					origs.push_back(adj);
					copias.push_back(copyAdj);
					copy->addAdj(copyAdj, w);
					q.push(adj);
				}
			}
		}
		return copyRoot;
	}

	template<typename T>
	NodoGraph<T>* NodoGraph<T>::spanningTree() {
		// Devuelve la raiz de un arbol de expansion (copia profunda) calculado por BFS.
		return spanningTreeAux(this);
	}

	// findPath: DFS que devuelve cualquier camino entre init y dest.
	// El conjunto de visitados es un vector (sin std::set ni std::unordered_set).
	template<typename T>
	bool findPathAux(NodoGraph<T>* cur, NodoGraph<T>* dest,
					 std::vector<NodoGraph<T>*>& path,
					 std::vector<NodoGraph<T>*>& vis) {
		path.push_back(cur);
		if (cur == dest) return true;
		vis.push_back(cur);
		for (auto& adjPair : cur->adjs) {
			if (indiceDe(vis, adjPair.first) >= 0) continue;
			if (findPathAux(adjPair.first, dest, path, vis)) return true;
		}
		path.pop_back();
		return false;
	}

	template<typename T>
	std::vector<NodoGraph<T>*> NodoGraph<T>::findPath(NodoGraph<T>* init, NodoGraph<T>* dest) {
		std::vector<NodoGraph<T>*> path;
		std::vector<NodoGraph<T>*> vis;
		findPathAux(init, dest, path, vis);
		return path;
	}

	template<typename T>
	std::vector<NodoGraph<T>*> AEDnames::NodoGraph<T>::findMinPath(NodoGraph<T>* init, NodoGraph<T>* dest) {
		// Dijkstra exacto usando nuestro Heap. El Heap es max-heap por prio,
		// asi que pasamos -dist como prio para sacar siempre el de menor distancia.
		// En vez de std::unordered_map usamos tres vectores paralelos: el nodo nodos[i]
		// tiene distancia dist[i] desde init y predecesor prev[i] en el camino minimo.
		std::vector<NodoGraph<T>*> nodos;
		std::vector<unsigned int> dist;
		std::vector<NodoGraph<T>*> prev;
		Heap<NodoGraph<T>*> pq;

		nodos.push_back(init);
		dist.push_back(0);
		prev.push_back(nullptr);
		pq.insert(init, 0);

		while (pq.size > 0) {
			NodoHeap<NodoGraph<T>*> top = pq.pop();
			NodoGraph<T>* u = top.dato;
			unsigned int d = static_cast<unsigned int>(-top.prio);
			int iu = indiceDe(nodos, u);
			// Si esta entrada esta desfasada (encontramos una mejor antes), la saltamos
			if (iu < 0 || d > dist[static_cast<size_t>(iu)]) continue;
			if (u == dest) break;
			for (auto& adjPair : u->adjs) {
				NodoGraph<T>* v = adjPair.first;
				unsigned int w = adjPair.second;
				unsigned int nd = d + w;
				int iv = indiceDe(nodos, v);
				if (iv < 0) {
					// Primera vez que llegamos a v: lo registramos
					nodos.push_back(v);
					dist.push_back(nd);
					prev.push_back(u);
					pq.insert(v, -static_cast<int>(nd));
				} else if (nd < dist[static_cast<size_t>(iv)]) {
					// Hemos encontrado un camino mas corto hasta v: lo actualizamos
					dist[static_cast<size_t>(iv)] = nd;
					prev[static_cast<size_t>(iv)] = u;
					pq.insert(v, -static_cast<int>(nd));
				}
			}
		}
		// Reconstruimos el camino desde dest siguiendo los predecesores
		std::vector<NodoGraph<T>*> path;
		if (indiceDe(nodos, dest) < 0) return path;
		NodoGraph<T>* cur = dest;
		while (cur != nullptr) {
			path.push_back(cur);
			int ic = indiceDe(nodos, cur);
			cur = (ic < 0) ? nullptr : prev[static_cast<size_t>(ic)];
		}
		std::reverse(path.begin(), path.end());
		return path;
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
		// Si el heap esta vacio devolvemos un NodoHeap por defecto en vez de crashear.
		if (arr.empty()) return NodoHeap<T>();
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
		// Recorrido lineal de hashesActive: si el hash esta registrado, devolvemos
		// su posicion en el array. Si no, -1.
		for (size_t i = 0; i < hashesActive.size(); ++i) {
			if (hashesActive[i] == hash) return static_cast<int>(i);
		}
		return -1;
	}
	template<typename T>
	bool AEDMap<T>::insert(T* value) {
		// Si el hash no tiene bucket asignado, creamos uno nuevo al final del array.
		// Despues empujamos el puntero en el bucket correspondiente.
		if (value == nullptr) return false;
		int h = badHash(value);
		int idx = hashToIndex(h);
		if (idx < 0) {
			hashesActive.push_back(h);
			table.push_back(std::vector<T*>());
			idx = static_cast<int>(hashesActive.size()) - 1;
		}
		table[static_cast<size_t>(idx)].push_back(value);
		return true;
	}
	template<typename T>
	bool AEDMap<T>::remove(T* value) {
		if (value == nullptr) return false;
		int h = badHash(value);
		int idx = hashToIndex(h);
		if (idx < 0) return false;
		auto& bucket = table[static_cast<size_t>(idx)];
		for (auto bit = bucket.begin(); bit != bucket.end(); ++bit) {
			if (*bit == value) {
				bucket.erase(bit);
				// Si el bucket queda vacio, borramos la clave del mapa (deja de estar presente)
				if (bucket.empty()) {
					hashesActive.erase(hashesActive.begin() + idx);
					table.erase(table.begin() + idx);
				}
				return true;
			}
		}
		return false;
	}
	//don't know why this returns int
	template<typename T>
	int AEDMap<T>::search(T* value) {
		// Devuelve la posicion dentro del bucket donde esta el puntero, o -1 si no existe.
		if (value == nullptr) return -1;
		int h = badHash(value);
		int idx = hashToIndex(h);
		if (idx < 0) return -1;
		auto& bucket = table[static_cast<size_t>(idx)];
		for (size_t i = 0; i < bucket.size(); ++i) {
			if (bucket[i] == value) return static_cast<int>(i);
		}
		return -1;
	}
	template<typename T>
	bool AEDMap<T>::contains(T* value) {
		return search(value) >= 0;
	}
	template<typename T>
	bool AEDMap<T>::isEmpty() {
		// El mapa esta vacio si no queda ninguna clave registrada
		return hashesActive.empty();
	}
	template<typename T>
	int AEDMap<T>::size() {
		// Numero total de elementos almacenados (suma de tamanyos de buckets)
		int total = 0;
		for (auto& bucket : table) total += static_cast<int>(bucket.size());
		return total;
	}
}