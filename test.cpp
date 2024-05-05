#include <bits/stdc++.h>
#include "directory.h"

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


    cout<<"HIJOS CHILDREN"<<endl; 
    arreglo_lista<FileNode *> children = dir.getRoot()->getChildren();
    for (FileNode* child : children) {
            cout<<child->getId()<<endl;
    }
    
    FileNode* f = dir.getRoot()->busquedaBinariaChildrenId(children, 2, 0, children.size());
    if ( f != nullptr ) { cout<<"Se encontro: "<<f->getId()<<endl; } else { cout<<"No se encontro"<<endl; }

    return EXIT_SUCCESS;
}