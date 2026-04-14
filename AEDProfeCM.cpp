// AEDProfeCMake.cpp: define el punto de entrada de la aplicación.
//

#include "AEDProfeCM.h"
#include "AEDProfeLib.h"

using namespace std;

int main()
{
	AEDnames::Nodo<int>* n = new AEDnames::Nodo<int>(0, nullptr, nullptr);
	cout << "Hello CMake." << n->getDato() << endl;
	return 0;
}
