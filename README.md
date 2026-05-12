# AED 2 — Estructuras de Datos no Lineales

Práctica 2 de la asignatura **Análisis y Diseño de Algoritmos** (UDIT).

C++20. Incluye dos partes:

- **Parte 1 — Hospital con punteros:** reimplementación del hospital de la práctica 1 con todas las estructuras almacenando punteros (`deque<Doctor*>`, `priority_queue<Paciente*>`, `list<Medicamento*>`, `stack<pair<Enfermedad*, Doctor*>>`, etc.).
- **Parte 2 — Estructuras no lineales:** árboles (`AEDTree`/`NodoTree`), grafos (`NodoGraph`), heap propio y mapa por hashing (`AEDMap`) sin usar `std::map` ni `std::unordered_map`.

## Build

Requiere CMake 3.16+ y un compilador C++20 (MSVC, g++ o clang).

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Se generan tres ejecutables:

- `AEDProfeCM` — tests del enunciado del profesor (Google Test).
- `Nolineales` / `smoke_nolineales` — smoke test standalone de la Parte 2 (sin Google Test).
- `HospitalP2` — demo del hospital de la Parte 1.

## Estructura

| Fichero | Contenido |
|---|---|
| `AEDProfeLib.h` / `AEDProfeLibI.h` / `AEDProfeLib.cpp` | Base: `Lista`, `SortedLista`, ordenaciones |
| `AEDNoLineales.h` / `AEDNoLinealesImp.h` | `NodoTree`, `AEDTree`, `NodoGraph`, `Heap`, `AEDMap` |
| `AEDProfeCM.h` / `AEDProfeCM.cpp` | `main` base |
| `AEDProfeCM_test.cpp` | Tests del profesor + 8 tests extra propios |
| `HospitalP2.h` / `HospitalP2.cpp` / `HospitalP2_main.cpp` | Hospital P2 con punteros + demo |
| `smoke_nolineales.cpp` | Smoke test sin Google Test |
| `CMakeLists.txt` | Configuración de build |

## Funcionalidad clave Parte 2

- **Árboles:** `breadthSpecial` (BFS de derecha a izquierda, ignorando hojas) y `depthSpecial` (DFS preorden con la misma regla).
- **Grafos:** `findPath` (DFS, cualquier camino) y `findMinPath` con **Dijkstra real** usando el `Heap` propio (camino de coste mínimo).
- **Heap:** max-heap por prioridad con `insert`/`pop` y mantenimiento de la propiedad de heap.
- **Mapa:** hashmap con buckets (`vector<vector<T*>>`) + array paralelo `vector<int> hashesActive` para rastrear los huecos activos. Cumple la restricción del enunciado de no usar contenedores asociativos de la STL.

## Tests

- **30 tests** entre los del enunciado y los 8 extras: covering Dijkstra real, colisiones de hashmap, casos límite del heap, recorridos de árboles y operaciones del hospital.
- 30/30 pasan, 0 crashes.

## Notas de implementación

Durante el desarrollo se han arreglado varios bugs del esqueleto base proporcionado (destructor de `NodoTree`, `Lista::reverse()`, `badHash` con cast incompatible, valores esperados incorrectos en algunos tests, etc.). Cada fix está comentado en el código.
