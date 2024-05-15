#include <bits/stdc++.h>
#include "avl_tree.h" // Incluye la definici�n de la clase AVL

using namespace std;

int main(){
    // Crear un nuevo �rbol AVL con un nodo ra�z de valor 0
    AVL *root = new AVL(0);

    // Insertar algunos nodos en el �rbol AVL
    root->insert(5);
    root = root->insert(root, 10);
    root = root->insert(root, 20);
    root = root->insert(root, 30);
    root = root->insert(root, 40);
    root = root->insert(root, 50);
    root = root->insert(root, 25);
    root->insert(70);
    root->insert(60);

    // Imprimir el �rbol en preorden
    root->preOrder(root);
    cout << endl;

    // Buscar un nodo con valor 25 en el �rbol
    if(root->search(25))
        cout << "Found" << endl;
    else
        cout << "Not Found" << endl;

    // Eliminar un nodo con valor 25 del �rbol
    root->remove(25);

    // Imprimir el �rbol en preorden despu�s de eliminar el nodo con valor 25
    root->preOrder(root);
    cout << endl;

    // Buscar nuevamente el nodo con valor 25 en el �rbol despu�s de la eliminaci�n
    if(root->search(25)){
        cout << "Found" << endl;
    }else{
        cout << "Not Found" << endl;
    }

    return EXIT_SUCCESS;
}
