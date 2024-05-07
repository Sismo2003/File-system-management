#ifndef PILA_H
#define PILA_H

#include <iostream>
#include <utility>

#define capacidad_pila 10 // Define la capacidad inicial de la pila

template <typename objeto>
class pila {
private:
    int i; // Índice que señala la próxima posición disponible en la pila
    int cap; // Capacidad máxima de la pila
    objeto* arr; // Puntero al arreglo que almacena los elementos de la pila

public:
    // Constructor que inicializa la pila con una capacidad específica
    explicit pila(int tam) : i{tam}, cap{i + capacidad_pila}, arr{new objeto[cap]} {}

    // Constructor de copia
    pila(const pila &rhs) : i{rhs.i}, cap{rhs.cap}, arr{new objeto[cap]} {
        // Copia los elementos del arreglo de la pila original al nuevo arreglo
        for (int k = 0; k < i; k++)
            arr[k] = rhs.arr[k];
    }

    // Constructor de movimiento
    pila(pila &&rhs) : i{rhs.i}, cap{rhs.cap}, arr{rhs.arr} {
        rhs.i = 0; // Restablece el índice de la pila original a cero
        rhs.cap = 0; // Restablece la capacidad de la pila original a cero
        rhs.arr = nullptr; // Establece el puntero de la pila original como nulo
    }

    // Constructor predeterminado que inicializa la pila con la capacidad predeterminada
    pila() : i{0}, cap{capacidad_pila}, arr{new objeto[capacidad_pila]} {}

    // Destructor de la pila
    ~pila() {
        delete[] arr; // Libera la memoria asignada al arreglo de la pila
    }

    // Operador de asignación por copia
    pila &operator=(const pila &rhs) {
        // Crea una copia de la pila original
        pila copia = rhs;
        // Intercambia las capacidades, los índices y los punteros de la pila actual con la copia
        std::swap(cap, copia.cap);
        std::swap(i, copia.i);
        std::swap(arr, copia.arr);
        return *this;
    }

    // Operador de asignación por movimiento
    pila &operator=(pila &&rhs) {
        // Intercambia las capacidades, los índices y los punteros de la pila actual con la pila original
        std::swap(cap, rhs.cap);
        std::swap(i, rhs.i);
        std::swap(arr, rhs.arr);
        return *this;
    }

    // Método para insertar un elemento al final de la pila (copia)
    void push(const objeto &rhs) {
        if (i == cap)
            reservar(cap + 1); // Invoca el método para aumentar el tamaño del arreglo si es necesario
        arr[i] = rhs; // Inserta el elemento en la posición i
        i++; // Incrementa el índice para señalar la próxima posición disponible
    }

    // Método para insertar un elemento al final de la pila (movimiento)
    void push(objeto &&rhs) {
        if (i == cap)
            reservar(cap + 1); // Invoca el método para aumentar el tamaño del arreglo si es necesario
        arr[i] = std::move(rhs); // Inserta el elemento en la posición i mediante movimiento
        i++; // Incrementa el índice para señalar la próxima posición disponible
    }

    // Método para eliminar el elemento en el tope de la pila
    void pop() {
        if (!vacia()) // Verifica si la pila no está vacía
            i--; // Decrementa el índice para eliminar el elemento en el tope de la pila
    }

    // Método para obtener una referencia al elemento en el tope de la pila
    objeto &tope() {
        if (!vacia()) // Verifica si la pila no está vacía
            return arr[i - 1]; // Devuelve una referencia al elemento en el tope de la pila
        throw std::runtime_error("Pila vacía"); // Lanza una excepción si la pila está vacía
    }

    // Método para obtener una referencia constante al elemento en el tope de la pila
    const objeto &tope() const {
        if (!vacia()) // Verifica si la pila no está vacía
            return arr[i - 1]; // Devuelve una referencia constante al elemento en el tope de la pila
        throw std::runtime_error("Pila vacía"); // Lanza una excepción si la pila está vacía
    }

    // Método que indica si la pila está vacía
    bool vacia(){
        return i == 0; // Retorna verdadero si el índice es cero, lo que indica que la pila está vacía
    }

    // Método que devuelve el tamaño actual de la pila
    int size() const {
        return i; // Retorna el valor del índice, que representa el tamaño actual de la pila
    }

    // Método para aumentar la capacidad del arreglo
    void reservar(int nueva_capacidad) {
        objeto* nuevo_arr = new objeto[nueva_capacidad]; // Crea un nuevo arreglo con la nueva capacidad
        // Copia los elementos del arreglo actual al nuevo arreglo
        for (int k = 0; k < i; k++) {
            nuevo_arr[k] = std::move(arr[k]);
        }
        delete[] arr; // Libera la memoria asignada al arreglo actual
        arr = nuevo_arr; // Asigna el nuevo arreglo al puntero de la pila
    }
};

#endif // PILA_H
