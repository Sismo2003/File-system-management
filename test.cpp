#include <bits/stdc++.h>
#include "avl_tree.h" // Incluye la definición de la clase AVL

using namespace std;

int main(){
    // Crear un nuevo árbol AVL con un nodo raíz de valor 0
    AVL *root = new AVL(0);

    // Insertar algunos nodos en el árbol AVL
    root->insert(5);
    root = root->insert(root, 10);
    root = root->insert(root, 20);
    root = root->insert(root, 30);
    root = root->insert(root, 40);
    root = root->insert(root, 50);
    root = root->insert(root, 25);
    root->insert(70);
    root->insert(60);

    // Imprimir el árbol en preorden
    root->preOrder(root);
    cout << endl;

    // Buscar un nodo con valor 25 en el árbol
    if(root->search(25))
        cout << "Found" << endl;
    else
        cout << "Not Found" << endl;

    // Eliminar un nodo con valor 25 del árbol
    root->remove(25);

    // Imprimir el árbol en preorden después de eliminar el nodo con valor 25
    root->preOrder(root);
    cout << endl;

    // Buscar nuevamente el nodo con valor 25 en el árbol después de la eliminación
    if(root->search(25)){
        cout << "Found" << endl;
    }else{
        cout << "Not Found" << endl;
    }

    return EXIT_SUCCESS;
}
