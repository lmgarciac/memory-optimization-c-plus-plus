//-----------------------------------
// MEMORY LEAKS
//-----------------------------------

// Un memory leak ocurre cuando se reserva memoria en el heap y nunca se libera.
// El puntero que la referenciaba se pierde, y el sistema operativo no puede recuperarla hasta que el programa termine.

// Este programa de pruebas fuga aproximadamente 2 GB de memoria.

// * Nota: Antes de ejecutar el programa abrir el administrador de tareas y observar el crecimiento desproporcionado
//   Del consumo de memorial del programa.

#include <iostream>

void createLeak(int count)
{
    for (int i = 0; i < count; ++i)
    {
        int* data = new int[1000];  // Reservamos 1000 ints (4 KB)
        
        data[0] = i;                // Ejecutamos alguna acción para evitar optimización
                                    // Compiladores como MSVC o Clang pueden optimizar y eliminar la reserva de memoria
                                    // Si identifican que no es útil.
        
        // delete[] data;           //Obviamos la liberación de memoria. (Si descomentamos la línea, el leak desaparece).
    }
}

int main()
{
    std::cout << "Starting memory leak demo...\n";

    for (int i = 0; i < 5000; ++i)
    {
        createLeak(100); // Cada llamada fuga ~400 KB
        if (i % 1000 == 0)
            std::cout << "Iteration " << i << " done\n";
    }

    std::cout << "\nLeak demo complete. Check memory usage now.\n";
    std::cout << "Press ENTER to exit...\n";
    std::cin.get(); // Pausa el programa hasta que presiones Enter
}
