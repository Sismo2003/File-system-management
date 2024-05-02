#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <utility>

#define capacidad_cola 10

template <typename objeto>
class cola {
private:
    int frente, final;
    int cap;
    objeto* arr;

public:
    explicit cola(int tam) : frente{0}, final{0}, cap{tam + capacidad_cola}, arr{new objeto[cap]} {}

    cola(const cola &rhs) : frente{rhs.frente}, final{rhs.final}, cap{rhs.cap}, arr{new objeto[cap]} {
        for (int k = frente; k != final; k = (k + 1) % cap)
            arr[k] = rhs.arr[k];
    }

    cola(cola &&rhs) : frente{rhs.frente}, final{rhs.final}, cap{rhs.cap}, arr{rhs.arr} {
        rhs.frente = 0;
        rhs.final = 0;
        rhs.cap = 0;
        rhs.arr = nullptr;
    }

    cola() : frente{0}, final{0}, cap{capacidad_cola}, arr{new objeto[capacidad_cola]} {}

    ~cola() {
        delete[] arr;
    }

    cola &operator=(const cola &rhs) {
        cola copia = rhs;
        std::swap(cap, copia.cap);
        std::swap(frente, copia.frente);
        std::swap(final, copia.final);
        std::swap(arr, copia.arr);
        return *this;
    }

    cola &operator=(cola &&rhs) {
        std::swap(cap, rhs.cap);
        std::swap(frente, rhs.frente);
        std::swap(final, rhs.final);
        std::swap(arr, rhs.arr);
        return *this;
    }

    void encolar(const objeto &rhs) {
        if ((final + 1) % cap == frente)
            reservar(cap + 1); // invocar metodo para aumentar el espacio
        arr[final] = rhs;
        final = (final + 1) % cap;
    }

    void encolar(objeto &&rhs) {
        if ((final + 1) % cap == frente)
            reservar(cap + 1); // invocar metodo para aumentar el espacio
        arr[final] = std::move(rhs);
        final = (final + 1) % cap;
    }

    void desencolar() {
        if (!vacia()) // metodo
            frente = (frente + 1) % cap;
    }

    objeto &frente_cola() {
        if (!vacia())
            return arr[frente];
        throw std::runtime_error("Cola vacía");
    }

    const objeto &frente_cola() const {
        if (!vacia())
            return arr[frente];
        throw std::runtime_error("Cola vacía");
    }

    bool vacia() const {
        return frente == final;
    }

    int size() const {
        return (final - frente + cap) % cap;
    }

    void reservar(int nueva_capacidad) {
        objeto* nuevo_arr = new objeto[nueva_capacidad];
        int j = 0;
        for (int k = frente; k != final; k = (k + 1) % cap) {
            nuevo_arr[j] = std::move(arr[k]);
            j++;
        }
        delete[] arr;
        arr = nuevo_arr;
        frente = 0;
        final = j;
        cap = nueva_capacidad;
    }
};

#endif // COLA_H
