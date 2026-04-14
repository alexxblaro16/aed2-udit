#pragma once
#include <vector>

namespace AEDnames {
	
	template<typename T>
	class NodoTree {
	public:
		T dato;
		NodoTree<T>* left;
		NodoTree<T>* right;
		NodoTree<T>* parent;
		NodoTree() { left = nullptr; right = nullptr; };
		NodoTree(int _dato, NodoTree* _left, NodoTree* _right)
			: dato(_dato), left(_left), right(_right) {
		}

		//Rule of 3: the expected 3 but we implement them to practice
		NodoTree(const NodoTree<T>& other) : dato(other.dato) {
			delete this->left;
			left = new NodoTree(*other.left);
			delete this->right;
			right = new NodoTree(*other.right);
		}
		NodoTree& operator=(const NodoTree<T>& other) {
			if (this != &other) {
				dato = other.dato;
				delete left;
				left = new NodoTree(*other.left);
				delete right;
				right = new NodoTree(*other.right);
			}
			return *this;
		}
		~NodoTree() {
			delete left;
			delete right;
			delete parent;
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
		std::vector<NodoGraph<T>*> findMinPath(NodoGraph<T>* init, NodoGraph<T>* dest);

	};

	template<typename T>
	class AEDMap {
		unsigned int lastindex = 0;
		//maps the hash of a value to the index of the bucket in the table where it is stored
		std::unordered_map<int, unsigned int> hashToIndexMap;
	public:
		std::vector<std::vector<T>> table;//inner vector is the bucket of objects with the same hash or key

		//not a real hash function
		int badHash(T* value);
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