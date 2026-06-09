#pragma once
#include <vector>
#include <algorithm>

namespace AEDnames {
	
	template<typename T>
	class NodoTree {
	public:
		T dato;
		NodoTree<T>* left;
		NodoTree<T>* right;
		NodoTree<T>* parent;
		NodoTree() : left(nullptr), right(nullptr), parent(nullptr) {};
		NodoTree(T _dato, NodoTree* _left, NodoTree* _right)
			: dato(_dato), left(_left), right(_right), parent(nullptr) {
		}

		//Rule of 3: the expected 3 but we implement them to practice
		NodoTree(const NodoTree<T>& other) : dato(other.dato), left(nullptr), right(nullptr), parent(nullptr) {
			// copia profunda solo si los hijos existen (evita UB con punteros sin inicializar)
			if (other.left) left = new NodoTree(*other.left);
			if (other.right) right = new NodoTree(*other.right);
		}
		NodoTree& operator=(const NodoTree<T>& other) {
			if (this != &other) {
				dato = other.dato;
				delete left;
				left = other.left ? new NodoTree(*other.left) : nullptr;
				delete right;
				right = other.right ? new NodoTree(*other.right) : nullptr;
			}
			return *this;
		}
		~NodoTree() {
			// NO borramos parent: el padre es propietario, no el hijo (evita doble delete)
			delete left;
			delete right;
		}

		bool isRoot();
		//these must work even if 'this' is not the root of the tree
		//distance between this node and root
		unsigned int getUpHeight();
		//distance between this node and the most distant leaf in its subtree
		unsigned int getDownHeight();
		//leftmost leaf in the subtree of this node
		NodoTree<T>* getleftleaf();
		//rightmost leaf in the subtree of this node
		NodoTree<T>* getrightleaf();
		//returns the root of the tree in which this node appears
		NodoTree<T>* getRoot();

	};
	template<typename T>
	class AEDTree {
	public:
		NodoTree<T>* root;
		AEDTree() { root = nullptr; }
		AEDTree(NodoTree<T>* _root) : root(_root) {}

		unsigned int getHeight();
		NodoTree<T>* getleftleaf();
		NodoTree<T>* getrightleaf();
		NodoTree<T>* getRoot();
		//must walk through the children from right to left and ignore the leaves
		std::vector<NodoTree<T>*> breadthSpecial();
		//must walk through the children from right to left and ignore the leaves
		std::vector<NodoTree<T>*> depthSpecial();
	};

	template<typename T>
	class NodoHeap {
	public:
		T dato;
		int prio;


		//by default inline
		bool operator<(const NodoHeap<T>& other) const {
			return this->prio < other.prio;
		}

	};

	template<typename T>
	class Heap {
	private:
		void upHeap(int i);
		void downHeap(int i);
	public:
		int size;
		std::vector <NodoHeap<T>> arr;
		Heap() { size = 0; arr.clear(); }

		void insert(T dato, int prio);
		NodoHeap<T> pop();

	};

	template<typename T>
	class NodoGraph {
	public:
		T dato;
		std::vector<std::pair<NodoGraph<T>*, unsigned int>> adjs;//adjacencies with wheights
		NodoGraph(T dato) : dato(dato) {}
		//by default inline
		bool operator==(const NodoGraph<T>& other) const {
			return dato == other.dato;
		}
		//by default inline comparing dato only, not adjs
		bool operator<(const NodoGraph<T>& other) const {
			return dato < other.dato;
		}

		void addAdj(NodoGraph<T>* adj, unsigned int weight) {
			if (adj != nullptr)
				this->adjs.push_back(std::make_pair(adj, weight));
		}
		void removeAdj(NodoGraph<T>* adj) {
			if (adj != nullptr) {
				this->adjs.erase(std::remove_if(this->adjs.begin(), this->adjs.end(),
					[adj](const std::pair<NodoGraph<T>*, unsigned int>& p) { return p.first == adj; }),
					this->adjs.end());
			}
		}
		NodoGraph<T>* search(T dato);
		//NOT OPTIMAL returns a tree formed by NodoGraph
		NodoGraph<T>* spanningTree();
		// Devuelve un camino cualquiera entre init y dest (DFS)
		std::vector<NodoGraph<T>*> findPath(NodoGraph<T>* init, NodoGraph<T>* dest);
		// Devuelve el camino minimo entre init y dest (Dijkstra con Heap propio)
		std::vector<NodoGraph<T>*> findMinPath(NodoGraph<T>* init, NodoGraph<T>* dest);

	};

	template<typename T>
	class AEDMap {
		// Vector paralelo: hashesActive[i] es la clave hash del bucket table[i].
		// Asi cumplimos con la restriccion del enunciado: solo array/vector/list,
		// nada de std::map ni std::unordered_map ni funciones hash de la std lib.
		std::vector<int> hashesActive;
	public:
		// El bucket guarda PUNTEROS (T*) para cumplir el criterio "guardar punteros a objetos"
		std::vector<std::vector<T*>> table;

		//not a real hash function
		int badHash(T* value);
		// Devuelve la posicion del bucket asociado a este hash en el array, o -1 si no existe.
		int hashToIndex(int hash);


		//should
		bool insert(T* value);
		bool remove(T* value);
		int search(T* value);
		bool contains(T* value);
		bool isEmpty();
		int size();

	};
}

#include "AEDNoLinealesImp.h"