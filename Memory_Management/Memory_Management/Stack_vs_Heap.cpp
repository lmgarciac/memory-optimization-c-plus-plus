//-----------------------------------
// STACK VS HEAP
//-----------------------------------
// Durante el ciclo de vida de un programa, se gestionan dos tipos de memoria principales: 
// La memoria stack y la memoria heap. 
// La stack se usa para variables locales, parámetros de funciones y llamadas a métodos, 
// con una asignación y desasignación automática y rápida (LIFO: Last In, First Out). 
// La heap almacena objetos y datos asignados dinámicamente, ofreciendo flexibilidad de tamaño y duración, 
// pero requiere gestión manual (en lenguajes como C/C++) o un recolector de basura (en lenguajes como Java o C#).

//-----------------------------------
// Stack:
//-----------------------------------
// - Administración automática del sistema (existen en un scope y se destruyen al salir de el)
// - Velocidad muy rápida
// - Tamaño limitado (algunos MBs)
// - Ciclo de vida mientras la función esté activa
// - Acceder al stack es un movimiento directo del puntero de pila.
// - Riesgo de Overflow (si se utiliza demasiada)

//-----------------------------------
// Heap:
//-----------------------------------
// - Administración manual (new/delete, malloc/free)
// - Velocidad mas lenta
// - Tamaño mayor
// - Ciclo de vida, hasta que se libere explícitamente
// - Acceder al heap requiere búsqueda, reserva y punteros, lo cual es mucho más costoso.
// - Riesgos: Memory leaks o Fragmentación
// - Un memory leak ocurre cuando se reserva memoria en el heap y nunca se libera.
//   El puntero que la referenciaba se pierde, y el sistema operativo no puede recuperarla hasta que el programa termine.
// - La fragmentación se da cuando el heap se llena con bloques dispersos de distintos tamaños.
//	 Con el tiempo, aunque haya memoria libre total, puede no haber un bloque contiguo suficientemente grande
//	 por lo que se pueden provocar crashes o caídas de rendimiento.


#include <iostream>
#include <chrono>
#include <vector>

int main() 
{
    constexpr int nHeap = 10000000;

    auto start_stack = std::chrono::high_resolution_clock::now();
    { //Utilizamos corchetes para delimitar el scope
        int arr[1000]; //Cambiar por un valor mayor provocará eventualmente un overflow de stack
        for (int i = 0; i < 1000; ++i) 
            arr[i] = i;
    }
    auto end_stack = std::chrono::high_resolution_clock::now();
    std::cout << "Stack small array done\n";

    // --- Heap allocation ---
    auto start_heap = std::chrono::high_resolution_clock::now();
    {
        int* arr = new int[nHeap];
        for (int i = 0; i < nHeap; ++i)     
            arr[i] = i;
        delete[] arr;
    }
    auto end_heap = std::chrono::high_resolution_clock::now();

    auto stack_time = std::chrono::duration_cast<std::chrono::microseconds>(end_stack - start_stack).count();
    auto heap_time = std::chrono::duration_cast<std::chrono::microseconds>(end_heap - start_heap).count();

    std::cout << "Stack section: " << stack_time << " uS\n";
    std::cout << "Heap section:  " << heap_time << " uS\n";
}
