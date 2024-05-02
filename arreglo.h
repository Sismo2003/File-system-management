#ifndef ARREGLO_LISTA_H
#define ARREGLO_LISTA_H

#include <iostream>
#include <utility>

#define capacidad 10

template <typename objeto>
class arreglo_lista {
private:
    int i;
    int cap;
    objeto* arr;

public:
    explicit arreglo_lista(int tam) : i{tam}, cap{i + capacidad}, arr{new objeto[cap]} {}

    arreglo_lista(const arreglo_lista &rhs) : i{rhs.i}, cap{rhs.cap}, arr{new objeto[cap]} {
        for (int k = 0; k < i; k++)
            arr[k] = rhs.arr[k];
    }

    arreglo_lista(arreglo_lista &&rhs) : i{rhs.i}, cap{rhs.cap}, arr{rhs.arr} {
        rhs.i = 0;
        rhs.cap = 0;
        rhs.arr = nullptr;
    }

    arreglo_lista() : i{0}, cap{capacidad}, arr{new objeto[capacidad]} {}

    ~arreglo_lista() {
        delete[] arr;
    }

    arreglo_lista &operator=(const arreglo_lista &rhs) {
        arreglo_lista copia = rhs;
        std::swap(cap, copia.cap);
        std::swap(i, copia.i);
        std::swap(arr, copia.arr);
        return *this;
    }

    arreglo_lista &operator=(arreglo_lista &&rhs) {
        std::swap(cap, rhs.cap);
        std::swap(i, rhs.i);
        std::swap(arr, rhs.arr);
        return *this;
    }

    void push_final(const objeto &rhs) {
        if (i == cap)
            reservar(cap + 1); // invocar metodo para aumentar el espacio
        arr[i] = rhs;
        i++;
    }

    void push_final(objeto &&rhs) {
        if (i == cap)
            reservar(cap + 1); // invocar metodo para aumentar el espacio
        arr[i] = std::move(rhs);
        i++;
    }

    void pop_final() {
        if (!vacia()) // metodo
            i--;
    }

    objeto &operator[] (int indice) {
        return arr[indice];
    }

    const objeto &operator[] (int indice) const {
        return arr[indice];
    }

    void nueva_capacidad(int nueva_cap) {
        if (nueva_cap > cap) {
            reservar(nueva_cap);
            cap = nueva_cap;
        }
    }

    void reservar(int nueva_capacidad) {
        objeto* nuevo_arr = new objeto[nueva_capacidad];
        for (int k = 0; k < i; k++) {
            nuevo_arr[k] = std::move(arr[k]);
        }
        delete[] arr;
        arr = nuevo_arr;
    }

    bool vacia(){
        return i == 0;
    }

	int size() const {
        return i;
	}

	void pop(int indice){
		if (indice < 0 || indice >= i) {
			std::cout << "Índice fuera de rango." << std::endl;
			return;
		}

		for (int j = indice; j < i - 1; ++j) {
			arr[j] = arr[j + 1];
		}

		i--;
	}

    objeto* begin() { return arr; }

    objeto* end() { return arr + i; }
};

#endif // ARREGLO_LISTA_H
