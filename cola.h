#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <utility>

#define capacidad_cola 10 // Capacidad predeterminada de la cola

template <typename objeto>
class cola {
private:
    int frente, final; // Índices de frente y final de la cola
    int cap; // Capacidad actual de la cola
    objeto* arr; // Puntero al arreglo que almacena los elementos de la cola

public:
    // Constructor que acepta un tamaño inicial para la cola
    explicit cola(int tam) : frente{0}, final{0}, cap{tam + capacidad_cola}, arr{new objeto[cap]} {}

    // Constructor de copia
    cola(const cola &rhs) : frente{rhs.frente}, final{rhs.final}, cap{rhs.cap}, arr{new objeto[cap]} {
        // Copia los elementos del arreglo de la cola original al nuevo arreglo
        for (int k = frente; k != final; k = (k + 1) % cap)
            arr[k] = rhs.arr[k];
    }

    // Constructor de movimiento
    cola(cola &&rhs) : frente{rhs.frente}, final{rhs.final}, cap{rhs.cap}, arr{rhs.arr} {
        // Mueve los datos de la cola original a la nueva cola y establece los valores de la cola original a valores predeterminados
        rhs.frente = 0;
        rhs.final = 0;
        rhs.cap = 0;
        rhs.arr = nullptr;
    }

    // Constructor predeterminado
    cola() : frente{0}, final{0}, cap{capacidad_cola}, arr{new objeto[capacidad_cola]} {}

    // Destructor
    ~cola() {
        delete[] arr;
    }

    // Operador de asignación de copia
    cola &operator=(const cola &rhs) {
        // Crea una copia de la cola y luego intercambia los valores de la copia con los valores de la cola actual
        cola copia = rhs;
        std::swap(cap, copia.cap);
        std::swap(frente, copia.frente);
        std::swap(final, copia.final);
        std::swap(arr, copia.arr);
        return *this;
    }

    // Operador de asignación de movimiento
    cola &operator=(cola &&rhs) {
        // Intercambia los valores de la cola actual con los valores de la cola movida
        std::swap(cap, rhs.cap);
        std::swap(frente, rhs.frente);
        std::swap(final, rhs.final);
        std::swap(arr, rhs.arr);
        return *this;
    }

    // Método para encolar un elemento en la cola (lvalue)
    void encolar(const objeto &rhs) {
        // Verifica si la cola está llena y, de ser así, aumenta la capacidad de la cola
        if ((final + 1) % cap == frente)
            reservar(cap + 1); // Invoca el método para aumentar el espacio
        arr[final] = rhs; // Agrega el elemento al final de la cola
        final = (final + 1) % cap; // Actualiza el índice final
    }

    // Método para encolar un elemento en la cola (rvalue)
    void encolar(objeto &&rhs) {
        // Verifica si la cola está llena y, de ser así, aumenta la capacidad de la cola
        if ((final + 1) % cap == frente)
            reservar(cap + 1); // Invoca el método para aumentar el espacio
        arr[final] = std::move(rhs); // Mueve el elemento al final de la cola
        final = (final + 1) % cap; // Actualiza el índice final
    }

    // Método para desencolar un elemento de la cola
    void desencolar() {
        // Verifica si la cola no está vacía y, de ser así, avanza el índice de frente
        if (!vacia()) // Método
            frente = (frente + 1) % cap;
    }

    // Método para obtener el elemento al frente de la cola (lvalue)
    objeto &frente_cola() {
        // Verifica si la cola no está vacía y, de ser así, devuelve el elemento al frente de la cola
        if (!vacia())
            return arr[frente];
        throw std::runtime_error("Cola vacía"); // Lanza una excepción si la cola está vacía
    }

    // Método para obtener el elemento al frente de la cola (rvalue)
    const objeto &frente_cola() const {
        // Verifica si la cola no está vacía y, de ser así, devuelve el elemento al frente de la cola
        if (!vacia())
            return arr[frente];
        throw std::runtime_error("Cola vacía"); // Lanza una excepción si la cola está vacía
    }

    // Método para verificar si la cola está vacía
    bool vacia() const {
        return frente == final; // La cola está vacía si el índice de frente y el índice final son iguales
    }

    // Método para obtener el tamaño actual de la cola
    int size() const {
        return (final - frente + cap) % cap; // Calcula el tamaño de la cola utilizando aritmética modular
    }

    // Método para reservar una nueva capacidad para la cola
    void reservar(int nueva_capacidad) {
        objeto* nuevo_arr = new objeto[nueva_capacidad]; // Crea un nuevo arreglo con la nueva capacidad
        int j = 0;
        // Copia los elementos del arreglo original al nuevo arreglo
        for (int k = frente; k != final; k = (k + 1) % cap) {
            nuevo_arr[j] = std::move(arr[k]); // Mueve los elementos en lugar de copiarlos
            j++;
        }
        delete[] arr; // Elimina el arreglo original
        arr = nuevo_arr; // Establece el puntero del arreglo al nuevo arreglo
        frente = 0; // Establece el índice de frente al principio del nuevo arreglo
        final = j; // Establece el índice final al final de los elementos copiados
        cap = nueva_capacidad; // Actualiza la capacidad de la cola
    }
};

#endif // COLA_H
