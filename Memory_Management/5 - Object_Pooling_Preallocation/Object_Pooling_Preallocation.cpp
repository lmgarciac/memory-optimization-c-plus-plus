//-----------------------------------
// OBJECT POOLING - PREALLOCATION
//-----------------------------------

//-----------------------------------
//	Casos prácticos
//-----------------------------------

//	Creación y destrucción constante de objetos (balas, enemigos, partículas).

//-----------------------------------
//	Problemas que trae
//-----------------------------------

//	Fragmentación del heap (múltiples alocaciones de memoria diferentes)
//	Pérdida de rendimiento (allocs y frees son lentas).
//	Inconsistencia en los tiempos por frame de acuerdo a la carga de trabajo que tenga cada uno.

//-----------------------------------
//  Soluciones prácticas
//-----------------------------------

//	Object Pooling : Creación de objetos una sola vez y su posterior reutilización.
//	Preallocation : Reserva de toda la memoria que se va a utilizar con anticipación.

//	*	Lo que aporta el object pooling y la preallocation es que no se hace new durante gameplay.
//	*	No se libera memoria en cada frame.
//	*	Todo vive en bloques contiguos lo que es excelente para el cache locality.


#include <iostream>
#include <vector>
#include <chrono>

struct Bullet {
    float x, y, vx, vy;
    bool active;
};

int main() {
    using clock = std::chrono::high_resolution_clock;

    const int totalObjects = 3'000'000;     //  Cantidad de objetos que necesitamos.
    const int objectPoolSize = 1000;        //  Tamaño del pool de objetos con el que trabajaremos.
                                            //  Ejemplo: 1000 balas activas simultáneas (nunca tendremos mas de esta cantidad).

    std::cout << "Test 1: new/delete por iteracion\n";
    {
        auto start = clock::now();

        for (int i = 0; i < totalObjects; ++i) {
            Bullet* b = new Bullet{ 0, 0, 1, 1, true }; // heap alloc
            b->x += b->vx;
            b->y += b->vy;
            delete b; // heap free
        }

        auto end = clock::now();
        std::chrono::duration<double> dt = end - start;
        std::cout << "Tiempo total (new/delete): " << dt.count() << " s\n";
    }

    std::cout << "\nTest 2: Object Pool (preallocation)\n";
    {
        auto start = clock::now();

        std::vector<Bullet> pool(objectPoolSize);   //  Creamos una sección de memoria para un pool de objetos
                                                    //  Unica operación de asignación de memoria en heap en lugar de múltiples
                                                    //  Fragmentación nula (bloque de datos contiguo)
                                                    //  (Adicionalmente, std::vector se ocupa de la asignación del puntero, el tamaño y la destrucción)
        for (auto& b : pool) {
            b.x = b.y = 0;
            b.vx = b.vy = 1;
            b.active = false;
        }

        for (int i = 0; i < totalObjects; ++i) {    // En un caso práctico, es muy factible que podamos reutilizar objetos ya creados en lugar de crear nuevos
            Bullet& b = pool[i % objectPoolSize];   // Simular reutilización (no asignamos nueva memoria)
            b.active = true;
            b.x += b.vx;
            b.y += b.vy;
        }

        auto end = clock::now();
        std::chrono::duration<double> dt = end - start;
        std::cout << "Tiempo total (pool):        " << dt.count() << " s\n";
    }

    std::cout << "\nPresione ENTER para salir...\n";
    std::cin.get();
}
