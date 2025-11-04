//-----------------------------------
// SMART POINTERS - OWNERSHIP
//-----------------------------------

//-----------------------------------
// Definiciones
//-----------------------------------

//	Los smart pointers son contenedores ligeros que encapsulan un puntero crudo (T*) y administran su ciclo de vida automáticamente.

//|--------------------------------------------------------------------------------------------------------------------------------------|
//| Tipo				 | Propósito	        | Propiedad(Ownership)	   | Costo			  | Uso típico								 |
//| -------------------- | -------------------- | ------------------------ | ---------------- | ---------------------------------------- |
//| `std::unique_ptr<T>` | Exclusivo		    | Un solo dueño			   | Cero overhead	  | RAII, recursos únicos					 |
//| `std::shared_ptr<T>` | Compartido			| Referencias múltiples	   | Contador atómico | Objetos compartidos(scripting, managers) |
//| `std::weak_ptr<T>`   | Referencia no dueña  | Observa un `shared_ptr`  | Muy bajo		  | Evitar ciclos de referencia				 |
//|--------------------------------------------------------------------------------------------------------------------------------------|

// En resumen:
// unique: Para casi todo en gameplay: entidades, recursos, buffers, etc.
// shared: Para sistemas donde varias partes comparten acceso a un recurso (por ejemplo, una textura o un sonido).

#include <iostream>
#include <memory>
#include <chrono>

struct Enemy {
    Enemy() { std::cout << "Spawn Enemy\n"; }
    ~Enemy() { std::cout << "Destroyed Enemy\n"; }
    float x = 0, y = 0;
};

struct EnemyCompare {
    EnemyCompare() { }
    ~EnemyCompare() { }
    float x = 0, y = 0;
};

int main() {

    std::cout << "\n\n=== USE CASES ===\n\n";

    //-------------------
    // Unique Pointer
    //-------------------
    {
        std::cout << "Unique Pointer Example: \n\n";

        std::unique_ptr<Enemy> e = std::make_unique<Enemy>();
        // e existe solo dentro de este scope
        std::cout << "Unique Pointer Enemy went out of scope\n";
    } // se destruye automáticamente aquí

    //-------------------
    // Shared Pointer
    //-------------------
    {
        std::cout << "\n\nShared Pointer Example: \n\n";

        std::shared_ptr<Enemy> a;
        {
            std::cout << "Create shared pointer\n";
            a = std::make_shared<Enemy>();
            std::cout << "Use count:" << a.use_count() << " \n";
            std::shared_ptr<Enemy> b = a; // contador = 2
            std::cout << "New assignment\n";
            std::cout << "Use count:" << a.use_count() << " \n";
        } // b sale de scope, contador = 1
        std::cout << "b outside scope\n";
        std::cout << "Use count:" << a.use_count() << " \n";
        std::cout << "a outside scope\n";
    } // a sale de scope, contador = 0, delete automático


    //-------------------
    // Comparativa
    //-------------------
    using clock = std::chrono::high_resolution_clock;
    const int iterations = 10'000'000;

    std::cout << "\n\n=== COMPARISON ===\n\n";

    std::cout << "=== Case 1: Raw Pointers ===\n";
    {
        auto start = clock::now();

        for (int i = 0; i < iterations; ++i) {
            EnemyCompare* e = new EnemyCompare();
            e->x += 1.0f;
            e->y += 1.0f;
            delete e;
        }

        auto end = clock::now();
        std::chrono::duration<double> dt = end - start;
        std::cout << "Total time (raw pointers): " << dt.count() << " s\n";
    }

    std::cout << "\n=== Case 2: unique_ptr ===\n";
    {
        auto start = clock::now();

        for (int i = 0; i < iterations; ++i) {
            std::unique_ptr<EnemyCompare> e = std::make_unique<EnemyCompare>();
            e->x += 1.0f;
            e->y += 1.0f;
        } // se destruye automáticamente al salir del scope

        auto end = clock::now();
        std::chrono::duration<double> dt = end - start;
        std::cout << "Total time (unique_ptr):   " << dt.count() << " s\n";
    }

    std::cout << "\n=== Case 3: shared_ptr ===\n";
    {
        auto start = clock::now();

        for (int i = 0; i < iterations; ++i) {
            std::shared_ptr<EnemyCompare> e = std::make_shared<EnemyCompare>();
            e->x += 1.0f;
            e->y += 1.0f;
        } // destrucción automática, pero con contador de referencias

        auto end = clock::now();
        std::chrono::duration<double> dt = end - start;
        std::cout << "Total time (shared_ptr):   " << dt.count() << " s\n";
    }

    std::cout << "\nPress ENTER to exit...\n";
    std::cin.get();
}