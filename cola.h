#ifndef COLA_H
#define COLA_H

#include <exception>
#include <string>
using namespace std;
class QueueException : public exception{
    private:
        string msg;
    public:
        explicit QueueException(const char* message) : msg(message){}
        explicit QueueException(const string& message) : msg(message){}
        virtual ~QueueException() throw () {}
        virtual const char* what() const throw() {
            return msg.c_str();
        }
};

//cola modelo circular
template <class T, int TAMANIO=1024>
class Cola
{
private:
    T arr[TAMANIO];
    int frontPos;
    int endPos;

    void copyAll(const Cola<T, TAMANIO>& q){
        frontPos = q.frontPos;
        endPos = q.endPos;
        for (int i=frontPos; i!=(endPos + 1) % TAMANIO; i = (i + 1) % TAMANIO) {
            arr[i] = q.arr[i];
        }
    };

public:
    Cola(){
        frontPos=0;
        endPos=TAMANIO-1;
    };
    Cola(const Cola<T, TAMANIO>& q){
        copyAll(q);
    };

    bool isEmpty(){
        return frontPos==endPos+1 || (frontPos==0 && endPos==TAMANIO-1);
    };
    bool isFull(){
        return frontPos==endPos+2
        || (frontPos==0 && endPos==TAMANIO-2)|| (frontPos==1 && endPos==TAMANIO-1);
        };

    void enqueue(const T& e){
        if(isFull()){
            throw QueueException("Desbordamiento de datos enqueue");
        }
        if(++endPos==TAMANIO){
            endPos=0;
        }
        arr[endPos]=e;
    };

    T dequeue(){
        if(isEmpty()){
            throw QueueException("Insuficiencia de datos, dequeue");
        }

         T result(arr[frontPos]);
        if(++frontPos==TAMANIO){
            frontPos=0;
        }
        return result;
    };
    T getFront(){
        if(isEmpty()){
            throw QueueException("Insuficiencia de datos, getFront");
        }
        return arr[frontPos];
    };

    Cola<T, TAMANIO>& operator = (const Cola<T, TAMANIO>& q){
        copyAll(q);
        return *this;
    };



};

#endif // COLA_H
