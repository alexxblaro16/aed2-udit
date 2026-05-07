// Smoke test: instancia las clases plantilla de Parte 2 para verificar que compilan.
// No es un test de verdad, solo provoca la instanciacion del codigo.

#include "AEDProfeLib.h"
#include "AEDNoLineales.h"
#include <iostream>

int main() {
    // Tree
    AEDnames::NodoTree<int>* root = new AEDnames::NodoTree<int>(0, nullptr, nullptr);
    AEDnames::NodoTree<int>* l = new AEDnames::NodoTree<int>(1, nullptr, nullptr);
    AEDnames::NodoTree<int>* r = new AEDnames::NodoTree<int>(2, nullptr, nullptr);
    root->left = l; root->right = r;
    AEDnames::AEDTree<int> tree(root);
    std::cout << "tree.getHeight()=" << tree.getHeight() << std::endl;
    auto bres = tree.breadthSpecial();
    std::cout << "breadthSpecial size=" << bres.size() << std::endl;

    // Heap
    AEDnames::Heap<int> h;
    h.insert(10, 2); h.insert(20, 5); h.insert(15, 3);
    std::cout << "Heap pop prio=" << h.pop().prio << std::endl;

    // Graph (sin new)
    AEDnames::NodoGraph<int> n1(1), n2(2), n3(3);
    n1.addAdj(&n2, 1); n1.addAdj(&n3, 10); n2.addAdj(&n3, 1);
    auto path = n1.findMinPath(&n1, &n3);
    std::cout << "findMinPath n1->n3 size=" << path.size() << " [";
    for (auto* p : path) std::cout << p->dato << " ";
    std::cout << "]" << std::endl;

    // Map
    AEDnames::AEDMap<int> m;
    int* v = new int(42);
    m.insert(v);
    std::cout << "map.size=" << m.size() << " contains=" << m.contains(v) << std::endl;
    m.remove(v);
    delete v;

    // Cleanup
    delete root;
    return 0;
}
