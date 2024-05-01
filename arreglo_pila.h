#ifndef ARREGLO_PILA_H
#define ARREGLO_PILA_H


#include <iostream>

#define capacidad 10

using namespace std;


template <typename Objeto>
class arreglo_pila
{
    private:
        int tope;
        int cap;
        Objeto *arr;
	public:
        explicit arreglo_pila (int tam):tope{tam},cap{tope+capacidad	}{
            arr=new Objeto[cap];
        }
        arreglo_pila (const arreglo_pila &rhs):tope{rhs.tope},cap{rhs.cap}, arr{nullptr}{
            arr=new Objeto[cap];
            for(int k=0;k<tope;k++)
            arr[k]=rhs.arr[k];
        }
        arreglo_pila(arreglo_pila &&rhs){
            rhs.tope=0;
            rhs.cap=0;
            rhs.arr=nullptr;
        }
        arreglo_pila(){
            tope=0;
            cap=capacidad;
            arr=new Objeto[capacidad];
        }
        ~arreglo_pila(){
            delete []arr;
        }
        arreglo_pila & operator = (const arreglo_pila &rhs){
            arreglo_pila copia=rhs;
            swap(*this, copia);
            return *this;
        }
        arreglo_pila & operator = (arreglo_pila &&rhs){
            swap(tope, rhs.tope);
            swap(cap, rhs.tope);
            swap(arr, rhs.arr);
            return *this;
        }

        int getTope(){
            return tope;
        }

        Objeto getElementoTope(){
            return arr[tope-1];//porque el tope aumento y el valor de tope es donde va entrar uno nuevo no del ultimo
        }

        void push(const Objeto &rhs){
            if(tope==cap){
                cap=cap+1;
                nueva_capacidad(cap);
            }
            arr[tope]=rhs;
            tope++;
        }
        void push(Objeto &&rhs){
            if(tope==cap){
                cap=cap+1;
                nueva_capacidad(cap);
            }
            arr[tope]=move(rhs);
            tope++;
        }



        void pop(){
            if(!vacia()){
                tope--;
            }
        }




        Objeto & operator [] (int indice){
            return arr[indice];
        }
        const Objeto & operator [](int indice)const{
            return arr[indice];
        }
        void nueva_capacidad(int nueva_cap){
            if(nueva_cap>cap){
                cap=nueva_cap;
                reservar(nueva_cap);
            }
        }
        void reservar(int nueva_capacidad){
            if(nueva_capacidad>cap){
                Objeto *nuevosDatos=new Objeto[nueva_capacidad];
                if(!vacia()){
                    for(int j=0; j<tope; j++){
                        nuevosDatos[j]=move(arr[j]);
                        arr=nuevosDatos;
                        delete []nuevosDatos;
                    }
                }
            }
        }
        int vacia(){
            if(tope==0)
            return 1;
            else
            return 0;
        }

        string toString(){
            string result;
            int i = 0;
            while(i<=tope){
                result+= arr[i].toString()+ "\n";
                i++;
            }
            return result;
        }

};


#endif // ARREGLO_PILA_H
