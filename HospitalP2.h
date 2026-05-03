#pragma once
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <iostream>
#include <utility>

// Reimplementacion de la practica 1 (Hospital) donde TODAS las estructuras
// de datos guardan punteros a objetos. La memoria dinamica de los elementos
// la gestiona el codigo cliente: las clases solo gestionan sus contenedores.
namespace HospitalP2 {

    class Doctor;

    class Medicamento {
    private:
        int id;
        std::string nombre;
        std::string tipo;
        int cantidad;

    public:
        Medicamento() : id(0), cantidad(0) {}
        Medicamento(int _id, std::string _nombre, std::string _tipo, int _cantidad)
            : id(_id), nombre(std::move(_nombre)), tipo(std::move(_tipo)), cantidad(_cantidad) {}

        bool operator==(const Medicamento& other) const { return id == other.id; }
        bool operator!=(const Medicamento& other) const { return !(*this == other); }
        bool operator<(const Medicamento& other) const {
            if (nombre != other.nombre) return nombre < other.nombre;
            return id < other.id;
        }

        int getId() const { return id; }
        void setId(int _id) { id = _id; }
        std::string getNombre() const { return nombre; }
        void setNombre(std::string _nombre) { nombre = std::move(_nombre); }
        std::string getTipo() const { return tipo; }
        void setTipo(std::string _tipo) { tipo = std::move(_tipo); }
        int getCantidad() const { return cantidad; }
        void setCantidad(int _cantidad) { cantidad = _cantidad; }

        // Crea un Medicamento NUEVO con la misma identidad pero cantidad k.
        // El llamante se encarga de liberar el puntero devuelto.
        Medicamento* copyCantidad(int k) const;
    };

    class Enfermedad {
    private:
        int id;
        std::string nombre;
        int letalidad;
        int urgencia;

    public:
        Enfermedad() : id(0), letalidad(0), urgencia(0) {}
        Enfermedad(int _id, std::string _nombre, int _letalidad, int _urgencia)
            : id(_id), nombre(std::move(_nombre)), letalidad(_letalidad), urgencia(_urgencia) {}

        int prioridad() const { return letalidad + urgencia; }

        bool operator==(const Enfermedad& other) const { return id == other.id; }
        bool operator<(const Enfermedad& other) const {
            if (prioridad() != other.prioridad()) return prioridad() < other.prioridad();
            return id < other.id;
        }

        int getId() const { return id; }
        std::string getNombre() const { return nombre; }
        int getLetalidad() const { return letalidad; }
        int getUrgencia() const { return urgencia; }
    };

    class Doctor {
    private:
        int id;
        std::string nombre;
        int dinero;
        // Lista de PUNTEROS a Enfermedad pendiente (no de objetos)
        std::list<Enfermedad*>* pendientes;

    public:
        Doctor() : id(0), dinero(0) { pendientes = new std::list<Enfermedad*>(); }
        Doctor(int _id, std::string _nombre, int _dinero)
            : id(_id), nombre(std::move(_nombre)), dinero(_dinero) {
            pendientes = new std::list<Enfermedad*>();
        }
        // Doctor toma propiedad de la lista que se le pasa (no copia)
        Doctor(int _id, std::string _nombre, int _dinero, std::list<Enfermedad*>* _pendientes)
            : id(_id), nombre(std::move(_nombre)), dinero(_dinero), pendientes(_pendientes) {}

        // Destructor: solo destruimos el contenedor, no los Enfermedad* dentro
        // (su propiedad puede estar compartida con el historial de un paciente).
        ~Doctor() { delete pendientes; }

        // Sin copia ni asignacion: gestionamos punteros crudos, evitamos copias accidentales.
        Doctor(const Doctor&) = delete;
        Doctor& operator=(const Doctor&) = delete;

        bool operator==(const Doctor& other) const { return id == other.id; }

        // Cobra todas las enfermedades pendientes y devuelve el total cobrado.
        int cobrar();

        int getId() const { return id; }
        std::string getNombre() const { return nombre; }
        int getDinero() const { return dinero; }
        void setDinero(int _dinero) { dinero = _dinero; }
        std::list<Enfermedad*>* getPendientes() const { return pendientes; }
    };

    class Paciente {
    private:
        int id;
        std::string nombre;
        // Lista de PUNTEROS a Enfermedad
        std::list<Enfermedad*>* enfermedades;
        // Pila de pares de PUNTEROS (Enfermedad*, Doctor*)
        std::stack<std::pair<Enfermedad*, Doctor*>>* historial;

    public:
        Paciente() : id(0) {
            enfermedades = new std::list<Enfermedad*>();
            historial = new std::stack<std::pair<Enfermedad*, Doctor*>>();
        }
        Paciente(int _id, std::string _nombre)
            : id(_id), nombre(std::move(_nombre)) {
            enfermedades = new std::list<Enfermedad*>();
            historial = new std::stack<std::pair<Enfermedad*, Doctor*>>();
        }
        Paciente(int _id, std::string _nombre,
                 std::list<Enfermedad*>* _enfermedades,
                 std::stack<std::pair<Enfermedad*, Doctor*>>* _historial)
            : id(_id), nombre(std::move(_nombre)),
              enfermedades(_enfermedades), historial(_historial) {}

        ~Paciente() {
            delete enfermedades;
            delete historial;
        }

        Paciente(const Paciente&) = delete;
        Paciente& operator=(const Paciente&) = delete;

        bool operator==(const Paciente& other) const { return id == other.id; }

        // Iterador a la enfermedad de mayor prioridad
        std::list<Enfermedad*>::iterator prioridadPaciente() const;
        // Saca y devuelve la enfermedad de mayor prioridad. El Doctor pasa a ser el responsable.
        Enfermedad* tratarEnfermedad(Doctor* d);
        void darAlta(Doctor* /*d*/) {}

        void insertEnfermedad(Enfermedad* e) { if (e) enfermedades->push_back(e); }

        // Comparacion por prioridad maxima de sus enfermedades (necesario para priority_queue)
        bool operator<(const Paciente& other) const;

        int getId() const { return id; }
        std::string getNombre() const { return nombre; }
        std::list<Enfermedad*>* getEnfermedades() const { return enfermedades; }
        std::stack<std::pair<Enfermedad*, Doctor*>>* getHistorial() const { return historial; }
    };

    // Comparador para usar Paciente* en una priority_queue (compara los objetos apuntados)
    struct PacientePtrCmp {
        bool operator()(Paciente* a, Paciente* b) const {
            if (a == nullptr || b == nullptr) return a < b;
            return (*a) < (*b);
        }
    };

    class Hospital {
    private:
        std::deque<Doctor*>* doctores;
        std::priority_queue<Paciente*, std::vector<Paciente*>, PacientePtrCmp>* urgencias;
        std::list<Medicamento*>* almacen;

    public:
        Hospital() {
            doctores = new std::deque<Doctor*>();
            urgencias = new std::priority_queue<Paciente*, std::vector<Paciente*>, PacientePtrCmp>();
            almacen = new std::list<Medicamento*>();
        }

        // Solo liberamos los contenedores; los objetos apuntados los gestiona el cliente.
        ~Hospital() {
            delete doctores;
            delete urgencias;
            delete almacen;
        }

        Hospital(const Hospital&) = delete;
        Hospital& operator=(const Hospital&) = delete;

        std::list<Medicamento*>* getAlmacen() { return almacen; }
        std::deque<Doctor*>* getDoctores() { return doctores; }

        void insertMedicamento(Medicamento* m) { if (m) almacen->push_back(m); }
        void insertPaciente(Paciente* p) { if (p) urgencias->push(p); }
        void insertDoctor(Doctor* d) { if (d) doctores->push_back(d); }

        // Devuelven listas NUEVAS de Medicamento* (objetos nuevos, hay que liberarlos)
        std::list<Medicamento*>* reponerStock_k(int k);
        std::list<Medicamento*>* reponerStock_niveles(std::list<Medicamento*>* nivelesAdecuados);
        // Pareja Doctor*-Paciente* atendidos. Devuelve nullptr si no hay disponibilidad.
        // El par devuelto es objeto nuevo; los punteros internos siguen pertenenciendo al hospital/cliente.
        std::pair<Doctor*, Paciente*>* treatPaciente();
        int pagarDoctores();
    };

} // namespace HospitalP2

// Operadores << para imprimir los objetos (no las estructuras, eso es solo para tests)
inline std::ostream& operator<<(std::ostream& os, const HospitalP2::Medicamento& m) {
    os << m.getNombre(); return os;
}
inline std::ostream& operator<<(std::ostream& os, const HospitalP2::Enfermedad& e) {
    os << e.getNombre(); return os;
}
inline std::ostream& operator<<(std::ostream& os, const HospitalP2::Doctor& d) {
    os << d.getNombre(); return os;
}
inline std::ostream& operator<<(std::ostream& os, const HospitalP2::Paciente& p) {
    os << p.getNombre(); return os;
}
