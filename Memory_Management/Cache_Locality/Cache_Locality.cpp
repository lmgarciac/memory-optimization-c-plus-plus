//-----------------------------------
// CACHE LOCALITY
//-----------------------------------

//  Los niveles de cache del procesador (L1, L2, L3) guardan los datos usados recientemente.
//  Tienen velocidades de acceso altamente superiores a la RAM.
//  Por ejemplo: L1: 1ns, L2: 3ns, L3: 12ns, RAM: 100nS

//  Si los datos están contiguos en memoria, el CPU los trae en un solo bloque (cache line).
//  Cache line: Bloque completo de memoria contigua (por ejemplo de 64 bytes).
//  Si están dispersos, la CPU necesita múltiples cache lines para traer un dato útil.
//  Hay "cache misses" y el CPU pierde tiempo esperando.

//-----------------------------------
// Cache Locality (localidad)
//-----------------------------------

//  Spatial locality: datos consecutivos en memoria (por ejemplo, un array).
//  Temporal locality: reutilización del mismo dato varias veces.
//  Un código “cache friendly” recorre datos de forma secuencial y mantiene estructuras compactas.

//-----------------------------------
// Posibles problemas
//-----------------------------------

//  Listas std::list o estructuras con muchos new generan datos dispersos en el heap (cache misses) 
//  por ende menor rendimiento, aunque el algoritmo sea el mismo.
//  (La lista salta de nodo en nodo por el heap, provocando cache misses).


#include <iostream>
#include <vector>
#include <list>
#include <chrono>

int main() {
    const int N = 10000000;
    using clock = std::chrono::high_resolution_clock;

    // Vector (contiguo)
    std::vector<int> vec(N);
    for (int i = 0; i < N; ++i) 
        vec[i] = i;

    auto t1 = clock::now();
    long long sum1 = 0;
    for (int i = 0; i < N; ++i)
        sum1 += vec[i]; //Traemos los datos al CPU
    auto t2 = clock::now();
    std::chrono::duration<double> dt1 = t2 - t1;

    // List (no contiguo)
    std::list<int> lst;
    for (int i = 0; i < N; ++i) 
        lst.push_back(i); //Reserva memoria en cualquier parte del heap con un new

    auto t3 = clock::now();
    long long sum2 = 0;
    for (int v : lst)
        sum2 += v; //Traemos los datos al CPU
    auto t4 = clock::now();
    std::chrono::duration<double> dt2 = t4 - t3;

    std::cout << "Vector time: " << dt1.count() << " s\n";
    std::cout << "List time:   " << dt2.count() << " s\n";
    std::cout << "Sums equal:  " << (sum1 == sum2 ? "yes" : "no") << "\n";
}
