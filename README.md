# C++ Memory Management & Performance Experiments

Este repositorio contiene una colección de **proyectos pequeños y autocontenidos en C++**, enfocados en **gestión de memoria, rendimiento y comportamiento real del hardware**.  
El objetivo es **didáctico y experimental**: observar efectos concretos como costos de asignación, fragmentación, cache locality y ownership, más allá de la teoría.

Cada proyecto es independiente y está pensado para **ejecutarse, medirse y analizarse**.

---

## Proyectos incluidos

### Stack vs Heap
Explora las diferencias fundamentales entre memoria **stack** y **heap**.

- Ciclo de vida y costos de acceso
- Límites de tamaño y riesgos (stack overflow)
- Comparación básica de tiempos usando `std::chrono`
- Ejemplo práctico con arrays en stack vs `new[]` en heap

Enfatiza por qué el stack es rápido pero limitado, y por qué el heap es flexible pero costoso.

---

### Memory Leaks
Demostración intencional de **fugas de memoria**.

- Reserva repetida de memoria en heap sin liberación
- Crecimiento progresivo del consumo de RAM
- Diseñado para observarse en tiempo real con el administrador de tareas

Ilustra cómo un leak ocurre incluso en código simple y por qué es crítico controlar ownership.

---

### Fragmentación del Heap / Allocators
Simulación de **fragmentación de memoria**.

- Asignaciones de tamaños variables
- Liberación parcial de bloques para generar huecos dispersos
- Escenario típico que puede llevar a `std::bad_alloc` aun con RAM disponible

Introduce el problema que justifica técnicas como pooling, preallocation y allocators custom.

---

### Cache Locality
Comparación directa entre estructuras **cache-friendly** y **cache-unfriendly**.

- `std::vector` (memoria contigua)
- `std::list` (nodos dispersos en heap)
- Medición de tiempos recorriendo grandes volúmenes de datos

Demuestra cómo la disposición en memoria puede importar más que el algoritmo.

---

### Object Pooling & Preallocation
Comparación entre:

- Creación/destrucción constante con `new/delete`
- Reutilización de objetos mediante **object pool prealocado**

Incluye:
- Simulación de objetos tipo gameplay (balas)
- Medición de tiempos totales
- Énfasis en estabilidad por frame y cache locality

Patrón clásico en motores de juegos y sistemas en tiempo real.

---

### Smart Pointers & Ownership
Exploración de **RAII y ownership moderno en C++**.

- `std::unique_ptr`
- `std::shared_ptr`
- `std::weak_ptr`
- Casos de uso típicos
- Comparación de costos frente a punteros crudos

Incluye un benchmark simple para visualizar el overhead real.

Reglas prácticas:
- `unique_ptr` para casi todo
- `shared_ptr` solo cuando el ownership realmente es compartido

---

## Requisitos

- C++17 o superior
- Compilador moderno (MSVC, Clang o GCC)
- No requiere librerías externas

---

## Objetivo del repositorio

Este repositorio **no busca ser una librería ni una solución productiva**, sino un espacio de:

- aprendizaje práctico
- experimentación
- observación empírica del comportamiento del sistema

Ideal para desarrolladores interesados en:
- engines
- juegos
- sistemas en tiempo real
- performance low-level

---

## Nota

Algunos ejemplos **consumen mucha memoria o tiempo de CPU** a propósito.  
Ejecutarlos con criterio y, si es posible, en entornos de prueba.

---

## Inspiración

Conceptos utilizados comúnmente en:
- desarrollo de videojuegos
- motores gráficos
- sistemas embebidos
- software de alto rendimiento

---

💡 *La memoria no es solo un recurso lógico: es una estructura física con costos reales.*
