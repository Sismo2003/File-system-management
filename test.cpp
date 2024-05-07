#include <bits/stdc++.h>
#include "directory.h"
#include "arreglo.h"



using namespace std;

    int main(){

    Directory dir;
    cout << dir.getCurrentDirectory()->getName() << endl;

    dir.createDirectory("dir1");
    dir.createDirectory("dir2");
    dir.createFile("file1");
    dir.setContent("file1", "Hola mundo");
    dir.setCurrentDirectory("dir1");

    cout << dir.getCurrentDirectory()->getName() << endl;

    dir.createFile("file2");
    dir.setContent("file2", "Hola mundo 2");

    dir.goToParentDirectory();

    cout << dir.getCurrentDirectory()->getName() << endl;

    dir.getAll();

    cout << dir.getContent("file1") << endl;

    cout<<endl;

    dir.setCurrentDirectory("dir1");
    dir.createDirectory("dir3");
    dir.setCurrentDirectory("dir3");
    dir.createDirectory("dir4");
    dir.setCurrentDirectory("dir4");
    dir.createFile("file3");
    dir.setContent("file3", "Hola mundo 3");


    FileNode* node1 = dir.findNodeInAll("file3");

    if(node1 != nullptr)
        cout << node1->getContent() << endl;
    else
        cout << "No se encontró el nodo" << endl;


    cout << "HIJOS CHILDREN ANTES DE ORDENAR" << endl;
    arreglo_lista<FileNode *> children = dir.getRoot()->getChildren();

    // Generar IDs aleatorios para cada nodo
    srand(time(nullptr)); // Inicializar la semilla para generar números aleatorios
    for (FileNode* child : children) {
        child->setId((rand() % 8) + 1); // Generar IDs aleatorios en el rango de 1 a 8
    }

    // Imprimir los IDs aleatorios de los nodos antes de ordenar
    for (FileNode* child : children) {
        cout << child->getId() << endl;
    }

     // Ordenar la lista de hijos por Id
    dir.sortDataQuick(0, children.size() -1, children);

    cout << "HIJOS CHILDREN DESPUES DE ORDENAR" << endl;
    for (FileNode* child : children) {
        cout << child->getId() << endl;
    }


    FileNode* f = dir.getRoot()->busquedaBinariaChildrenId(children, 2, 0, children.size());
    if ( f != nullptr ) { cout<<"Se encontro: "<<f->getId()<<endl; } else { cout<<"No se encontro"<<endl; }






    return EXIT_SUCCESS;
}
