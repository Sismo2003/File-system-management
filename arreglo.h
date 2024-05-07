#ifndef ARREGLO_LISTA_H
#define ARREGLO_LISTA_H

#include <iostream>
#include <utility>

#define capacidad 10 // Capacidad predeterminada del arreglo

template <typename objeto>
class arreglo_lista {
private:
    int i; // Índice que señala al próximo espacio libre en el arreglo
    int cap; // Capacidad actual del arreglo
    objeto* arr; // Puntero al arreglo que almacena los elementos

public:
    // Constructor que acepta un tamaño inicial para el arreglo
    explicit arreglo_lista(int tam) : i{tam}, cap{i + capacidad}, arr{new objeto[cap]} {}

    // Constructor de copia
    arreglo_lista(const arreglo_lista &rhs) : i{rhs.i}, cap{rhs.cap}, arr{new objeto[cap]} {
        // Copia los elementos del arreglo original al nuevo arreglo
        for (int k = 0; k < i; k++)
            arr[k] = rhs.arr[k];
    }

    // Constructor de movimiento
    arreglo_lista(arreglo_lista &&rhs) : i{rhs.i}, cap{rhs.cap}, arr{rhs.arr} {
        // Mueve los datos del arreglo original al nuevo arreglo y establece los valores del arreglo original a valores predeterminados
        rhs.i = 0;
        rhs.cap = 0;
        rhs.arr = nullptr;
    }

    // Constructor predeterminado
    arreglo_lista() : i{0}, cap{capacidad}, arr{new objeto[capacidad]} {}

    // Destructor
    ~arreglo_lista() {
        delete[] arr; // Libera la memoria asignada para el arreglo
    }

    // Operador de asignación de copia
    arreglo_lista &operator=(const arreglo_lista &rhs) {
        // Crea una copia de la lista y luego intercambia los valores de la copia con los valores de la lista actual
        arreglo_lista copia = rhs;
        std::swap(cap, copia.cap);
        std::swap(i, copia.i);
        std::swap(arr, copia.arr);
        return *this;
    }

    // Operador de asignación de movimiento
    arreglo_lista &operator=(arreglo_lista &&rhs) {
        // Intercambia los valores de la lista actual con los valores de la lista movida
        std::swap(cap, rhs.cap);
        std::swap(i, rhs.i);
        std::swap(arr, rhs.arr);
        return *this;
    }

    // Método para agregar un elemento al final del arreglo (lvalue)
    void push_final(const objeto &rhs) {
        // Verifica si el arreglo está lleno y, de ser así, aumenta la capacidad del arreglo
        if (i == cap)
            reservar(cap + 1); // Invoca el método para aumentar el espacio
        arr[i] = rhs; // Agrega el elemento al final del arreglo
        i++; // Incrementa el índice que señala al próximo espacio libre
    }

    // Método para agregar un elemento al final del arreglo (rvalue)
    void push_final(objeto &&rhs) {
        // Verifica si el arreglo está lleno y, de ser así, aumenta la capacidad del arreglo
        if (i == cap)
            reservar(cap + 1); // Invoca el método para aumentar el espacio
        arr[i] = std::move(rhs); // Mueve el elemento al final del arreglo
        i++; // Incrementa el índice que señala al próximo espacio libre
    }

    // Método para eliminar el último elemento del arreglo
    void pop_final() {
        // Verifica si el arreglo no está vacío y, de ser así, decrementa el índice que señala al próximo espacio libre
        if (!vacia()) // Método
            i--;
    }

    // Sobrecarga del operador de acceso [] para acceder a los elementos del arreglo
    objeto &operator[] (int indice) {
        return arr[indice]; // Devuelve una referencia al elemento en la posición indicada por el índice
    }

    // Sobrecarga del operador de acceso [] constante para acceder a los elementos del arreglo (solo lectura)
    const objeto &operator[] (int indice) const {
        return arr[indice]; // Devuelve una referencia constante al elemento en la posición indicada por el índice
    }

    // Método para establecer una nueva capacidad para el arreglo
    void nueva_capacidad(int nueva_cap) {
        if (nueva_cap > cap) {
            reservar(nueva_cap); // Invoca el método para reservar un nuevo espacio de memoria para el arreglo
            cap = nueva_cap; // Actualiza la capacidad del arreglo
        }
    }

    // Método para reservar una nueva capacidad para el arreglo
    void reservar(int nueva_capacidad) {
        objeto* nuevo_arr = new objeto[nueva_capacidad]; // Crea un nuevo arreglo con la nueva capacidad
        for (int k = 0; k < i; k++) {
            nuevo_arr[k] = std::move(arr[k]); // Mueve los elementos del arreglo original al nuevo arreglo
        }
        delete[] arr; // Libera la memoria asignada para el arreglo original
        arr = nuevo_arr; // Establece el puntero del arreglo al nuevo arreglo
    }

    // Método para verificar si el arreglo está vacío
    bool vacia(){
        return i == 0; // El arreglo está vacío si el índice que señala al próximo espacio libre es igual a cero
    }

    // Método para obtener el tamaño actual del arreglo
    int size() const {
        return i; // Devuelve el número de elementos actualmente almacenados en el arreglo
    }

    // Método para eliminar un elemento del arreglo en una posición específica
    void pop(int indice){
        if (indice < 0 || indice >= i) {
            std::cout << "Índice fuera de rango." << std::endl; // Imprime un mensaje de error si el índice está fuera de rango
            return;
        }

        for (int j = indice; j < i - 1; ++j) {
            arr[j] = arr[j + 1]; // Desplaza los elementos hacia la izquierda para llenar el espacio dejado por el elemento eliminado
        }

        i--; // Decrementa el índice que señala al próximo espacio libre
    }

    // Iterador para acceder al primer elemento del arreglo
    objeto* begin() { return arr; }

    // Iterador para acceder al último elemento del arreglo
    objeto* end() { return arr + i; }
};

#endif // ARREGLO_LISTA_H
