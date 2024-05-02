#ifndef PILA_H
#define PILA_H

#include <iostream>
#include <utility>

#define capacidad_pila 10

template <typename objeto>
class pila {
private:
    int i;
    int cap;
    objeto* arr;

public:
    explicit pila(int tam) : i{tam}, cap{i + capacidad_pila}, arr{new objeto[cap]} {}

    pila(const pila &rhs) : i{rhs.i}, cap{rhs.cap}, arr{new objeto[cap]} {
        for (int k = 0; k < i; k++)
            arr[k] = rhs.arr[k];
    }

    pila(pila &&rhs) : i{rhs.i}, cap{rhs.cap}, arr{rhs.arr} {
        rhs.i = 0;
        rhs.cap = 0;
        rhs.arr = nullptr;
    }

    pila() : i{0}, cap{capacidad_pila}, arr{new objeto[capacidad_pila]} {}

    ~pila() {
        delete[] arr;
    }

    pila &operator=(const pila &rhs) {
        pila copia = rhs;
        std::swap(cap, copia.cap);
        std::swap(i, copia.i);
        std::swap(arr, copia.arr);
        return *this;
    }

    pila &operator=(pila &&rhs) {
        std::swap(cap, rhs.cap);
        std::swap(i, rhs.i);
        std::swap(arr, rhs.arr);
        return *this;
    }

    void push(const objeto &rhs) {
        if (i == cap)
            reservar(cap + 1); // invocar metodo para aumentar el espacio
        arr[i] = rhs;
        i++;
    }

    void push(objeto &&rhs) {
        if (i == cap)
            reservar(cap + 1); // invocar metodo para aumentar el espacio
        arr[i] = std::move(rhs);
        i++;
    }

    void pop() {
        if (!vacia()) // metodo
            i--;
    }

    objeto &tope() {
        if (!vacia())
            return arr[i - 1];
        throw std::runtime_error("Pila vacía");
    }

    const objeto &tope() const {
        if (!vacia())
            return arr[i - 1];
        throw std::runtime_error("Pila vacía");
    }

    bool vacia(){
        return i == 0;
    }

	int size() const {
        return i;
	}

    void reservar(int nueva_capacidad) {
        objeto* nuevo_arr = new objeto[nueva_capacidad];
        for (int k = 0; k < i; k++) {
            nuevo_arr[k] = std::move(arr[k]);
        }
        delete[] arr;
        arr = nuevo_arr;
    }
};

#endif // PILA_H
