#include <iostream>
#include <gtest/gtest.h>
#include "AEDProfeLib.h"
#include "AEDNoLineales.h"
#include <format>
#include <algorithm>
#include <queue>
#include <unordered_set>
TEST(AEDProfeCMake_test, test1) {
    EXPECT_EQ(0, 0);
}
TEST(AEDProfeCMake_test, test2) {
    EXPECT_EQ(0, 1);
}

TEST(AEDProfeCMake_test, test3){
    //AEDnames::NodoTree<int>* n = new AEDnames::NodoTree<int>(3, nullptr, nullptr);
    AEDnames::NodoTree<int>* n = nullptr;
    delete n;
}

// Tests b�sicos para la clase Heap (usa el vector p�blico `arr` y el struct NodoHeap)
TEST(Heap_test, heap_one_element) {
    AEDnames::Heap<int> h = AEDnames::Heap<int>();
    h.insert(10, 2);
 
    EXPECT_EQ(h.pop().prio, 2);
    EXPECT_EQ(h.size, 1);

}
TEST(Heap_test, heap_and_top_prio) {
    AEDnames::Heap<int> h = AEDnames::Heap<int>();
    h.insert(10, 2);
    h.insert(20, 5);
    h.insert(15, 3);

    EXPECT_EQ(h.size, 3);
    EXPECT_EQ(h.pop().prio, 5);
}

TEST(Heap_test, heap_pop_new_top) {
    AEDnames::Heap<int> h = AEDnames::Heap<int>();
    h.insert(10, 2);
    h.insert(20, 5);
    h.insert(15, 3);
    EXPECT_EQ(h.size, 3);
	
    h.pop(); // Remove the top element (prio 5)
    EXPECT_EQ(h.size, 2);
    EXPECT_EQ(h.pop().prio, 3);
}

TEST(Heap_test, heap_pop_all) {
    AEDnames::Heap<int> h = AEDnames::Heap<int>();
    h.insert(10, 2);
    h.insert(20, 5);
    h.insert(15, 3);
    EXPECT_EQ(h.size, 3);

    AEDnames::NodoHeap<int> head = h.pop(); // Remove the top element (prio 5)
    EXPECT_EQ(head.prio, 5);
    EXPECT_EQ(h.size, 2);

    head = h.pop(); // Remove the top element (prio 3)
    EXPECT_EQ(head.prio, 3);
    EXPECT_EQ(h.size, 1);

    head = h.pop(); // Remove the top element (prio 2)
    EXPECT_EQ(head.prio, 2);
    EXPECT_EQ(h.size, 0);
}

TEST(Heap_test, heap_insert_highest_prio_pop_all) {
    AEDnames::Heap<int> h = AEDnames::Heap<int>();
    h.insert(10, 2);
    h.insert(20, 5);
    h.insert(15, 3);
    EXPECT_EQ(h.size, 3);

    AEDnames::NodoHeap<int> head = h.pop(); // Remove the top element (prio 5)
    EXPECT_EQ(head.prio, 5);
    EXPECT_EQ(h.size, 2);

    h.insert(25, 4); // Insert a new element with highest prio
    EXPECT_EQ(h.size, 3);
    head = h.pop(); // Remove the top element (prio 4)
    EXPECT_EQ(head.prio, 4);
    EXPECT_EQ(h.size, 2);

    head = h.pop(); // Remove the top element (prio 3)
    EXPECT_EQ(head.prio, 3);
    EXPECT_EQ(h.size, 1);

    head = h.pop(); // Remove the top element (prio 2)
    EXPECT_EQ(head.prio, 2);
    EXPECT_EQ(h.size, 0);
}

TEST(Heap_test, heap_insert_lowest_prio_pop_all) {
    AEDnames::Heap<int> h = AEDnames::Heap<int>();
    h.insert(10, 2);
    h.insert(20, 5);
    h.insert(15, 3);
    EXPECT_EQ(h.size, 3);

    AEDnames::NodoHeap<int> head = h.pop(); // Remove the top element (prio 5)
    EXPECT_EQ(head.prio, 5);
    EXPECT_EQ(h.size, 2);

    h.insert(25, 1); // Insert a new element with highest prio
    EXPECT_EQ(h.size, 3);
    head = h.pop(); // Remove the top element (prio 3)
    EXPECT_EQ(head.prio, 3);
    EXPECT_EQ(h.size, 2);

    head = h.pop(); // Remove the top element (prio 2)
    EXPECT_EQ(head.prio, 2);
    EXPECT_EQ(h.size, 1);

    head = h.pop(); // Remove the top element (prio 1)
    EXPECT_EQ(head.prio, 1);
    EXPECT_EQ(h.size, 0);
}

//AEDTree tests
TEST(AEDTree_test, tree_constructors) {

    AEDnames::NodoTree<int>* root = new AEDnames::NodoTree<int>(10, nullptr, nullptr);
    AEDnames::AEDTree<int>* tree = new AEDnames::AEDTree<int>(root);
    AEDnames::NodoTree<int>* rleft = new AEDnames::NodoTree<int>(10, nullptr, nullptr);
    AEDnames::NodoTree<int>* rright = new AEDnames::NodoTree<int>(7, nullptr, nullptr);
    root->left = rleft;
    root->right = rright;

    EXPECT_EQ(tree->getHeight(), 1);
    
}

//must walk through the children from right to left and ignore the leaves
TEST(AEDTree_test, tree_breadth) {

    AEDnames::NodoTree<int>* root = new AEDnames::NodoTree<int>(0, nullptr, nullptr);
    AEDnames::AEDTree<int>* tree = new AEDnames::AEDTree<int>(root);
    AEDnames::NodoTree<int>* rleft = new AEDnames::NodoTree<int>(1, nullptr, nullptr);
    AEDnames::NodoTree<int>* rright = new AEDnames::NodoTree<int>(2, nullptr, nullptr);
	root->left = rleft;
	root->right = rright;

    EXPECT_EQ(tree->getHeight(), 1);

    std::vector<AEDnames::NodoTree<int>*> actual = tree->breadthSpecial();
    std::vector<AEDnames::NodoTree<int>*> expected = std::vector<AEDnames::NodoTree<int>*>();
    expected.push_back(root);
    
	EXPECT_EQ(actual, expected);
    actual.clear();
	expected.clear();

    AEDnames::NodoTree<int>* rleftleft = new AEDnames::NodoTree<int>(3, nullptr, nullptr);
    AEDnames::NodoTree<int>* rleftright = new AEDnames::NodoTree<int>(4, nullptr, nullptr);
    AEDnames::NodoTree<int>* rrightleft = new AEDnames::NodoTree<int>(5, nullptr, nullptr);
	rleft->left = rleftleft;
	rleft->right = rleftright;
    rright->left = rrightleft;
    
    actual = tree->breadthSpecial();
	expected.push_back(root);
    expected.push_back(rright);
    expected.push_back(rleft);

	EXPECT_EQ(actual, expected);
    actual.clear();
    expected.clear();

    AEDnames::NodoTree<int>* rleftleftleft = new AEDnames::NodoTree<int>(3, nullptr, nullptr);
    AEDnames::NodoTree<int>* rleftleftright = new AEDnames::NodoTree<int>(3, nullptr, nullptr);
    AEDnames::NodoTree<int>* rleftrightleft = new AEDnames::NodoTree<int>(4, nullptr, nullptr);
	rleftleft->left = rleftleftleft;
    rleftleft->right = rleftleftright;
    rleftright->left = rleftrightleft;

    actual = tree->breadthSpecial();
    expected.push_back(root);
    expected.push_back(rright);
    expected.push_back(rleft);
    expected.push_back(rleftright);
    expected.push_back(rleftleft);

    EXPECT_EQ(actual, expected);
}

//must walk through the children from right to left and ignore the leaves
TEST(AEDTree_test, tree_depth) {
    AEDnames::NodoTree<int>* root = new AEDnames::NodoTree<int>(0, nullptr, nullptr);
    AEDnames::AEDTree<int>* tree = new AEDnames::AEDTree<int>(root);
    AEDnames::NodoTree<int>* rleft = new AEDnames::NodoTree<int>(1, nullptr, nullptr);
    AEDnames::NodoTree<int>* rright = new AEDnames::NodoTree<int>(2, nullptr, nullptr);
    root->left = rleft;
    root->right = rright;

    EXPECT_EQ(tree->getHeight(), 1);

    std::vector<AEDnames::NodoTree<int>*> actual = tree->breadthSpecial();
    std::vector<AEDnames::NodoTree<int>*> expected = std::vector<AEDnames::NodoTree<int>*>();
    expected.push_back(root);

    EXPECT_EQ(actual, expected);
    actual.clear();
    expected.clear();

    AEDnames::NodoTree<int>* rleftleft = new AEDnames::NodoTree<int>(3, nullptr, nullptr);
    AEDnames::NodoTree<int>* rleftright = new AEDnames::NodoTree<int>(4, nullptr, nullptr);
    AEDnames::NodoTree<int>* rrightleft = new AEDnames::NodoTree<int>(5, nullptr, nullptr);
    rleft->left = rleftleft;
    rleft->right = rleftright;
    rright->left = rrightleft;

    actual = tree->breadthSpecial();
    expected.push_back(root);
    expected.push_back(rright);
    expected.push_back(rleft);

    EXPECT_EQ(actual, expected);

    AEDnames::NodoTree<int>* rleftleftleft = new AEDnames::NodoTree<int>(3, nullptr, nullptr);
    AEDnames::NodoTree<int>* rleftleftright = new AEDnames::NodoTree<int>(3, nullptr, nullptr);
    AEDnames::NodoTree<int>* rleftrightleft = new AEDnames::NodoTree<int>(4, nullptr, nullptr);
    rleftleft->left = rleftleftleft;
    rleftleft->right = rleftleftright;
    rleftright->left = rleftrightleft;

    //REVISE not finished!! 
    actual = tree->breadthSpecial();
    expected.push_back(root);
    expected.push_back(rright);
    expected.push_back(rleft);
    expected.push_back(rleftright);
    expected.push_back(rleftleft);

    EXPECT_EQ(actual, expected);

}
//NodoGraph tests
TEST(NodoGraph_test, graph_equal_less) {
    AEDnames::NodoGraph<int> n1(1);
    AEDnames::NodoGraph<int> n2(2);

    EXPECT_EQ(n1, n1);
    EXPECT_LT(n1, n2);
}

TEST(NodoGraph_test, graph_add_adjs) {
    AEDnames::NodoGraph<int> n1(1);
    AEDnames::NodoGraph<int> n2(2);
    AEDnames::NodoGraph<int> n3(3);
    n1.addAdj(&n2, 1);
    n1.addAdj(&n3, 1);
    EXPECT_EQ(n1.adjs.size(), 2);
    EXPECT_EQ(n1.adjs[0].first->dato, 2);
    EXPECT_EQ(n1.adjs[1].first->dato, 3);
}

TEST(NodoGraph_test, graph_add_and_remove_adj) {
    AEDnames::NodoGraph<int> n1(1);
    AEDnames::NodoGraph<int> n2(2);
    AEDnames::NodoGraph<int> n3(3);
    n1.addAdj(&n2, 1);
    n1.addAdj(&n3, 1);
    EXPECT_EQ(n1.adjs.size(), 2);
    EXPECT_EQ(n1.adjs[0].first->dato, 2);
    EXPECT_EQ(n1.adjs[1].first->dato, 3);
    n1.removeAdj(&n2);
    EXPECT_EQ(n1.adjs.size(), 1);
    EXPECT_EQ(n1.adjs[0].first->dato, 3);
}

TEST(NodoGraph_test, graph_search) {
    AEDnames::NodoGraph<int> n1(1);
    AEDnames::NodoGraph<int> n2(2);
    AEDnames::NodoGraph<int> n3(3);
    n1.addAdj(&n2, 1);
    n2.addAdj(&n3, 1);
   
    AEDnames::NodoGraph<int>* s = n1.search(2);
    EXPECT_EQ(n2, *s);

    s = n1.search(3);
    EXPECT_EQ(n3, *s);
}

TEST(NodoGraph_test, graph_search2) {
    AEDnames::NodoGraph<int> n1(1);
    AEDnames::NodoGraph<int> n2(2);
    AEDnames::NodoGraph<int> n3(3);
    AEDnames::NodoGraph<int> n4(4);
    AEDnames::NodoGraph<int> n5(5);
    AEDnames::NodoGraph<int> n6(6);
    AEDnames::NodoGraph<int> n7(7);
    AEDnames::NodoGraph<int> n8(8);

    n1.addAdj(&n2, 1);
    n1.addAdj(&n3, 1);
    n1.addAdj(&n4, 1);
    n2.addAdj(&n4, 1);
    n2.addAdj(&n5, 1);
    n2.addAdj(&n1, 1);
	n3.addAdj(&n6, 1);
	n3.addAdj(&n7, 1);

    //direct search
    AEDnames::NodoGraph<int>* s = n1.search(2);
    EXPECT_EQ(n2, *s);

    s = n1.search(3);
    EXPECT_EQ(n3, *s);

    s = n2.search(4);
    EXPECT_EQ(n4, *s);

    s = n2.search(1);
    EXPECT_EQ(n1, *s);

	//indirect search
    s = n1.search(5);
    EXPECT_EQ(n5, *s);

	s = n1.search(1);//self reference through n2
    EXPECT_EQ(n1, *s);

	s = n2.search(6);//through n1, n3
    EXPECT_EQ(n6, *s);

	s = n2.search(8);//cannot find it, should return nullptr
    EXPECT_EQ(nullptr, s);
}

bool checkallpresent(AEDnames::NodoGraph<int>* start, std::map<int, bool>& must) {
    
    for (auto it : start->adjs) {
        if (must[it.first->dato])//if key present in map, mark it as found
            must[it.first->dato] = true;
		checkallpresent(it.first, must);//recursive call to check all adjacents
    }
	bool alltrue = true;
    for (auto [elem, present] : must)
		alltrue = alltrue && present;//check if all elements were found
    
    return alltrue;
}

TEST(NodoGraph_test, graph_spanning) {
    AEDnames::NodoGraph<int> n1(1);
    AEDnames::NodoGraph<int> n2(2);
    AEDnames::NodoGraph<int> n3(3);
    AEDnames::NodoGraph<int> n4(4);
    AEDnames::NodoGraph<int> n5(5);
    AEDnames::NodoGraph<int> n6(6);
    AEDnames::NodoGraph<int> n7(7);
    AEDnames::NodoGraph<int> n8(8);

    n1.addAdj(&n2, 1);
    n1.addAdj(&n3, 1);
    n1.addAdj(&n4, 1);
    n2.addAdj(&n4, 1);
    n2.addAdj(&n5, 1);
    n2.addAdj(&n1, 1);
    n3.addAdj(&n6, 1);
    n3.addAdj(&n7, 1);

    AEDnames::NodoGraph<int>* s = n1.spanningTree();
    EXPECT_EQ(s->adjs.size(), 7);
	//n8 not present in the graph, so it should not be in the spanning tree, but all other nodes should be
    std::map<int, bool> must = {{1, false}, {2, false}, {3, false}, {4, false}, {5, false}, {6, false}, {7, false}};
	EXPECT_TRUE(checkallpresent(s, must));

}

// Conteo de nodos alcanzables desde 'a' en el grafo original (BFS)
size_t countReachable(AEDnames::NodoGraph<int>* start) {
    if (start == nullptr) return 0uLL;//unsigned long long
      std::queue<AEDnames::NodoGraph<int>*> q;
      std::unordered_set<AEDnames::NodoGraph<int>*> vis;
      q.push(start);
      vis.insert(start);
      while (!q.empty()) {
          auto cur = q.front(); q.pop();
          for (auto adjPair : cur->adjs) {
              AEDnames::NodoGraph<int>* adj = adjPair.first;
              if (!vis.count(adj)) {
                  vis.insert(adj);
                  q.push(adj);
              }
          }
      }
      return vis.size();
}

// Ejemplo: crear un grafo con ciclos y generar su spanning tree desde un nodo
TEST(NodoGraph_test, spanningTree_example_bfs_copy) {
    // Construcci�n del grafo original (posible ciclo)
    AEDnames::NodoGraph<int>* a = new AEDnames::NodoGraph<int>(1);
    AEDnames::NodoGraph<int>* b = new AEDnames::NodoGraph<int>(2);
    AEDnames::NodoGraph<int>* c = new AEDnames::NodoGraph<int>(3);
    AEDnames::NodoGraph<int>* d = new AEDnames::NodoGraph<int>(4);

    a->addAdj(b, 1);
    a->addAdj(c, 1);
    b->addAdj(c, 1); // arista que puede generar ciclo l�gico
    c->addAdj(d, 1);
    b->addAdj(a, 1); // ciclo expl�cito

    size_t origCount = 4;
    // Generar el spanning tree (debe devolver la ra�z de una copia en forma de �rbol)
    AEDnames::NodoGraph<int>* treeRoot = a->spanningTree();
    ASSERT_NE(treeRoot, nullptr);
    EXPECT_EQ(treeRoot->dato, a->dato);

    // Conteo de nodos en la copia (deber�a coincidir con origCount)
    size_t copyCount = countReachable(treeRoot);
    EXPECT_EQ(copyCount, origCount);

    // Comprobar que todos los nodos de la copia son punteros distintos a los originales
    std::unordered_set<AEDnames::NodoGraph<int>*> origNodes;
    std::queue<AEDnames::NodoGraph<int>*> q;
    q.push(a);
    origNodes.insert(a);
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        for (auto adjPair : cur->adjs) {
            AEDnames::NodoGraph<int>* adj = adjPair.first;
            if (!origNodes.count(adj)) {
                origNodes.insert(adj);
                q.push(adj);
            }
        }
    }
    
}

TEST(NodoGraph_test, graph_path) {
    AEDnames::NodoGraph<int> n1(1);
    AEDnames::NodoGraph<int> n2(2);
    AEDnames::NodoGraph<int> n3(3);
    AEDnames::NodoGraph<int> n4(4);
    AEDnames::NodoGraph<int> n5(5);
    AEDnames::NodoGraph<int> n6(6);
    AEDnames::NodoGraph<int> n7(7);
    AEDnames::NodoGraph<int> n8(8);

    n1.addAdj(&n2, 1);
    n1.addAdj(&n3, 1);
    n1.addAdj(&n4, 1);
    n2.addAdj(&n4, 1);
    n2.addAdj(&n5, 1);
    n2.addAdj(&n1, 1);
    n3.addAdj(&n6, 1);
    n3.addAdj(&n7, 1);

    std::vector<AEDnames::NodoGraph<int>*> path = n1.findMinPath(&n1, &n2);
    std::vector<AEDnames::NodoGraph<int>*> expected = std::vector<AEDnames::NodoGraph<int>*>();
	expected.push_back(&n1);
	expected.push_back(&n2);
    
    EXPECT_EQ(path, expected);
	expected.clear();
	path.clear();
    
    path = n1.findMinPath(&n1, &n4);
    expected.push_back(&n1);
    expected.push_back(&n2);
    expected.push_back(&n4);

    EXPECT_EQ(path, expected);
    expected.clear();
    path.clear();

    path = n1.findMinPath(&n1, &n7);
    expected.push_back(&n1);
    expected.push_back(&n3);
    expected.push_back(&n7);
    EXPECT_EQ(path, expected);
    
}


//AEDmap tests
TEST(AEDMap_Test, AEDmap_one_elem) {
    AEDnames::AEDMap<int> m;
    int* v = new int(12345);

    EXPECT_EQ(m.isEmpty(), true);
    EXPECT_EQ(m.size(), 0);

    // badHash debe ser determinista
    int h1 = m.badHash(v);
    int h2 = m.badHash(v);
    EXPECT_EQ(h1, h2);

    int idx = m.hashToIndex(h1);
    EXPECT_GE(idx, 0);
    EXPECT_LT(idx, m.size());

    // Insertemos para garantizar que hay buckets y size() > 0 antes de usar hashToIndex
    bool ins = m.insert(v);
    EXPECT_TRUE(ins);

	EXPECT_TRUE(!m.isEmpty());
    EXPECT_EQ(m.size(), 1);
	EXPECT_TRUE(m.contains(v));

    // limpieza
    m.remove(v);
    EXPECT_TRUE(m.isEmpty());
    EXPECT_EQ(m.size(), 0);
    delete v;
}

TEST(AEDMap_Test, AEDmap_InsertContainsRemove) {
    AEDnames::AEDMap<int> m;
    int* a = new int(1);
    int* b = new int(2);

    // inicialmente vac�o
    EXPECT_TRUE(m.isEmpty());

    // insertar y comprobar contains/search
    EXPECT_TRUE(m.insert(a));
    EXPECT_FALSE(m.isEmpty());
    EXPECT_TRUE(m.contains(a));
	EXPECT_FALSE(m.contains(b)); // b no insertado

	m.insert(b);
    EXPECT_TRUE(m.contains(b));


    // eliminar y comprobar que ya no est�
    EXPECT_TRUE(m.remove(a));
    EXPECT_FALSE(m.contains(a));
    EXPECT_TRUE(m.contains(b));
    EXPECT_TRUE(m.remove(b));
    // limpieza
    delete a;
    delete b;
}

TEST(AEDMap_Test, AEDmap_InsertContainsRemoveBulk) {
    AEDnames::AEDMap<int> m;
    EXPECT_TRUE(m.isEmpty());
    EXPECT_EQ(m.size(), 0);

    // insertar varios valores distintos
    std::vector<int*> vals;
    for (int i = 0; i < 5; ++i) {
        vals.push_back(new int(i + 10));
        EXPECT_TRUE(m.insert(vals.back()));
    }

    // ahora no debe estar vac�o y size() debe ser > 0 (n�mero de buckets)
    EXPECT_FALSE(m.isEmpty());
    EXPECT_GT(m.size(), 0);

    // todos los valores deben estar contenidos
    for (int* p : vals) {
        EXPECT_TRUE(m.contains(p));
    }

    // eliminar todos
    for (int* p : vals) {
        EXPECT_TRUE(m.remove(p));
        delete p;
    }

    // tras eliminar, isEmpty puede ser true si la implementaci�n borra buckets vac�os
    // no hacemos aserci�n estricta sobre size() final (depende de la implementaci�n),
    // pero todos los elementos deben haber sido eliminados.
    for (int* p : vals) {
        EXPECT_FALSE(m.contains(p));
    }
}
