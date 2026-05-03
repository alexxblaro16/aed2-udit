#include "HospitalP2.h"

namespace HospitalP2 {

    // --- MEDICAMENTO ---
    Medicamento* Medicamento::copyCantidad(int k) const {
        // Devuelve un Medicamento NUEVO con la misma identidad pero distinta cantidad.
        return new Medicamento(id, nombre, tipo, k);
    }

    // --- DOCTOR ---
    int Doctor::cobrar() {
        // Cobra todas las enfermedades pendientes acumulando su prioridad.
        // Vaciamos la lista pero NO borramos las Enfermedad* (las puede tener el historial del paciente).
        if (pendientes->empty()) return 0;
        int total = 0;
        while (!pendientes->empty()) {
            Enfermedad* e = pendientes->front();
            pendientes->pop_front();
            if (e) total += e->prioridad();
        }
        return total;
    }

    // --- PACIENTE ---
    std::list<Enfermedad*>::iterator Paciente::prioridadPaciente() const {
        if (enfermedades->empty()) return enfermedades->end();
        auto maxIt = enfermedades->begin();
        for (auto it = enfermedades->begin(); it != enfermedades->end(); ++it) {
            // Comparamos por prioridad de la Enfermedad apuntada
            if ((*maxIt) == nullptr) { maxIt = it; continue; }
            if ((*it) == nullptr) continue;
            if ((*maxIt)->prioridad() < (*it)->prioridad()) {
                maxIt = it;
            }
        }
        return maxIt;
    }

    Enfermedad* Paciente::tratarEnfermedad(Doctor* /*d*/) {
        // Saca el puntero de la enfermedad mas prioritaria de la lista.
        // No la borra: el caller la puede meter en pendientes del doctor y en el historial.
        if (enfermedades->empty()) return nullptr;
        auto it = prioridadPaciente();
        Enfermedad* e = *it;
        enfermedades->erase(it);
        return e;
    }

    bool Paciente::operator<(const Paciente& other) const {
        // Comparacion por prioridad maxima de las enfermedades del paciente.
        // Usado por la priority_queue: el de mayor prioridad sale primero.
        int miP = 0;
        if (!enfermedades->empty()) {
            auto it = prioridadPaciente();
            if (*it) miP = (*it)->prioridad();
        }
        int suP = 0;
        if (!other.getEnfermedades()->empty()) {
            int maxVal = -1;
            for (auto it = other.getEnfermedades()->begin(); it != other.getEnfermedades()->end(); ++it) {
                if (*it && (*it)->prioridad() > maxVal) maxVal = (*it)->prioridad();
            }
            suP = maxVal < 0 ? 0 : maxVal;
        }
        return miP < suP;
    }

    // --- HOSPITAL ---
    std::list<Medicamento*>* Hospital::reponerStock_k(int k) {
        // Devuelve una lista NUEVA con Medicamentos NUEVOS (copias con la diferencia que falta).
        auto* compra = new std::list<Medicamento*>();
        for (Medicamento* med : *almacen) {
            if (med == nullptr) continue;
            if (med->getCantidad() < k) {
                compra->push_back(med->copyCantidad(k - med->getCantidad()));
            }
        }
        return compra;
    }

    std::list<Medicamento*>* Hospital::reponerStock_niveles(std::list<Medicamento*>* nivelesAdecuados) {
        auto* compra = new std::list<Medicamento*>();
        if (nivelesAdecuados == nullptr) return compra;
        for (Medicamento* nivel : *nivelesAdecuados) {
            if (nivel == nullptr) continue;
            for (Medicamento* med : *almacen) {
                if (med == nullptr) continue;
                if (med->getId() == nivel->getId()) {
                    if (med->getCantidad() < nivel->getCantidad()) {
                        compra->push_back(med->copyCantidad(nivel->getCantidad() - med->getCantidad()));
                    }
                    break;
                }
            }
        }
        return compra;
    }

    std::pair<Doctor*, Paciente*>* Hospital::treatPaciente() {
        // Atendemos: sacamos un doctor y el paciente mas urgente.
        if (doctores->empty() || urgencias->empty()) return nullptr;

        Doctor* d = doctores->front();
        doctores->pop_front();
        Paciente* p = urgencias->top();
        urgencias->pop();
        if (d == nullptr || p == nullptr) return nullptr;

        // El paciente entrega la enfermedad mas urgente al doctor.
        Enfermedad* e = p->tratarEnfermedad(d);
        if (e != nullptr) {
            p->getHistorial()->push(std::make_pair(e, d));
            d->getPendientes()->push_back(e);
        }

        // El doctor vuelve al final de la cola.
        doctores->push_back(d);
        // El paciente vuelve a urgencias si aun tiene enfermedades pendientes.
        if (!p->getEnfermedades()->empty()) urgencias->push(p);

        return new std::pair<Doctor*, Paciente*>(d, p);
    }

    int Hospital::pagarDoctores() {
        // Cada doctor cobra sus pendientes y se le ingresa la cantidad.
        int total = 0;
        for (Doctor* doctor : *doctores) {
            if (doctor == nullptr) continue;
            int pago = doctor->cobrar();
            doctor->setDinero(doctor->getDinero() + pago);
            total += pago;
        }
        return total;
    }

} // namespace HospitalP2
