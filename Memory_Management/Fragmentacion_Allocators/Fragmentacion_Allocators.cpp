//-----------------------------------
// FRAGMENTACION
//-----------------------------------

//	La fragmentación ocurre cuando la memoria libre del heap queda partida en muchas partes pequeñas y no contiguas
//	Aunque haya espacio total libre, no hay un bloque grande y continuo para nuevas reservas, el sistema debe buscar, reorganizar o incluso fallar

//-----------------------------------
//	Posibles consecuencias:
//-----------------------------------
//	Rendimiento inconsistente. Algunos frames tardan mucho más que otros
//	Micro stuttering. Pequeños saltos de frame
//	Crash por “bad_alloc” incluso con RAM disponible

//-----------------------------------
// Soluciones Posibles
//-----------------------------------

//  Object pooling. Reservar objetos una vez y reusarlos.
//  Preallocation. Reservar grandes bloques al inicio.
//  Custom allocators. Manejar tu propia memoria para tipos de datos específicos.
//  Frame allocators. Reservar todo lo que se necesita por frame y liberar de golpe.

//-----------------------------------
//  Ejemplo de Fragmentación
//-----------------------------------
//  Esto ejemplo simplemente simula asignación de memoria fragmentada.

#include <iostream>
#include <vector>
#include <cstdlib>

int main() {
    std::cout << "Simulando fragmentacion del heap...\n";

    std::vector<int*> blocks;

    // Reservamos muchos bloques de distintos tamaños
    for (int i = 0; i < 1000000; ++i) {
        int size = rand() % 1000 + 1; // tamaño variable (entre 1 y 1000)
        blocks.push_back(new int[size]);
    }

    // liberamos algunos al azar (fragmentación)
    for (int i = 0; i < 1000000; i += 3) {
        delete[] blocks[i];
        blocks[i] = nullptr;
    }

    std::cout << "Se genera fragmentacion: bloques libres dispersos.\n";
    std::cout << "Presione ENTER para salir y liberar todo...\n";
    std::cin.get();

    // Liberamos el resto
    for (auto ptr : blocks)
        delete[] ptr;

    return 0;
}
