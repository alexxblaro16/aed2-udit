// Demostracion simple del hospital con punteros: crea medicamentos, doctores y
// pacientes (todos con new) y ejercita las operaciones del Hospital. Limpia la
// memoria al final.

#include "HospitalP2.h"

using namespace HospitalP2;

int main() {
    Hospital hospital;

    // Stock de medicamentos
    Medicamento* m1 = new Medicamento(1, "Ibuprofeno", "antiinflamatorio", 30);
    Medicamento* m2 = new Medicamento(2, "Paracetamol", "analgesico", 5);
    Medicamento* m3 = new Medicamento(3, "Amoxicilina", "antibiotico", 0);
    hospital.insertMedicamento(m1);
    hospital.insertMedicamento(m2);
    hospital.insertMedicamento(m3);

    // Doctores
    Doctor* d1 = new Doctor(1, "Dr. Garcia", 100);
    Doctor* d2 = new Doctor(2, "Dra. Lopez", 200);
    hospital.insertDoctor(d1);
    hospital.insertDoctor(d2);

    // Enfermedades (objetos que iran rotando entre listas)
    Enfermedad* e1 = new Enfermedad(1, "Gripe", 3, 2);
    Enfermedad* e2 = new Enfermedad(2, "Apendicitis", 8, 9);
    Enfermedad* e3 = new Enfermedad(3, "Fractura", 5, 6);

    // Pacientes
    Paciente* p1 = new Paciente(1, "Ana");
    p1->insertEnfermedad(e1);
    p1->insertEnfermedad(e2);
    Paciente* p2 = new Paciente(2, "Bruno");
    p2->insertEnfermedad(e3);

    hospital.insertPaciente(p1);
    hospital.insertPaciente(p2);

    // Reposicion de stock con nivel k=20: m1(30)>=20 no se compra, m2(5) compra 15, m3(0) compra 20.
    std::list<Medicamento*>* compra = hospital.reponerStock_k(20);
    std::cout << "Medicamentos a comprar (k=20):";
    for (Medicamento* m : *compra) std::cout << " " << m->getNombre() << "(" << m->getCantidad() << ")";
    std::cout << std::endl;
    // Los medicamentos devueltos son objetos NUEVOS, hay que liberarlos
    for (Medicamento* m : *compra) delete m;
    delete compra;

    // Atender pacientes (uno por iteracion)
    while (auto* par = hospital.treatPaciente()) {
        std::cout << "Atendido: " << par->first->getNombre() << " -> " << par->second->getNombre() << std::endl;
        delete par;
    }

    // Pagar a los doctores
    int totalPagado = hospital.pagarDoctores();
    std::cout << "Total pagado a doctores: " << totalPagado << std::endl;

    // Limpieza explicita de la memoria que ha creado el cliente
    delete e1; delete e2; delete e3;
    delete p1; delete p2;
    delete d1; delete d2;
    delete m1; delete m2; delete m3;

    return 0;
}
