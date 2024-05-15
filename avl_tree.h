//
// Created by Alexis Ortiz ceceña on 09/05/24 and fixed in totaly by Iker Yared Covarrubias Famoso.
//

#ifndef FILE_SYSTEM_MANAGEMENT_DATA_STRUCTURE_2024A_AVL_TREE_H
#define FILE_SYSTEM_MANAGEMENT_DATA_STRUCTURE_2024A_AVL_TREE_H

// Inclusión de bibliotecas estándar de C++
#include <bits/stdc++.h>
using namespace std;

// Definición de la clase AVL (árbol AVL)
class AVL
{
private:
    int key;         // Valor del nodo
    AVL* root = nullptr;  // Puntero a la raíz del árbol
    AVL* left;       // Puntero al hijo izquierdo
    AVL* right;      // Puntero al hijo derecho
    int height;      // Altura del nodo en el árbol

public:
    // Constructor
    AVL(int k) : key(k), left(nullptr), right(nullptr), height(1) {}

    // Métodos públicos

    // Realiza un recorrido en preorden del árbol
    void preOrder()
    {
        preOrder(root);
    }

    // Métodos privados

    // Obtiene la altura de un nodo
    int getHeight(AVL *N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    // Obtiene el balance de un nodo (diferencia de alturas entre hijos izquierdo y derecho)
    int getBalance(AVL *N) {
        if (N == nullptr)
            return 0;
        return getHeight(N->left) - getHeight(N->right);
    }

    // Rotación a la derecha
    AVL *rightRotate(AVL *y) {
        AVL *x = y->left;
        AVL *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Rotación a la izquierda
    AVL *leftRotate(AVL *x) {
        AVL *y = x->right;
        AVL *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // Inserta un nodo en el árbol AVL
    void insert(int key){
        root = insert(this, key);
    }

    // Inserta un nodo en el árbol AVL de forma recursiva
    AVL* insert(AVL* node, int key){
        if (node == nullptr)
            return(new AVL(key));

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Realiza un recorrido en preorden del árbol de forma recursiva
    void preOrder(AVL *root)
    {
        if(root != nullptr)
        {
            cout << root->key << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    // Realiza una búsqueda en profundidad (DFS) en el árbol para verificar si una clave está presente
    bool search(int key) {
        return search(this, key);
    }

    // Realiza una búsqueda en profundidad (DFS) en el árbol de forma recursiva
    bool search(AVL* node, int key) {
        if (node == nullptr)
            return false;
        if (key == node->key)
            return true;
        if (key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    // Elimina un nodo del árbol AVL
    void remove(int key){
        root = remove(this, key);
    }

    // Elimina un nodo del árbol AVL de forma recursiva
    AVL* remove(AVL* root, int key) {
        if (root == nullptr)
            return root;

        // Si la clave a eliminar es menor que la clave del nodo actual,
        // entonces debe estar en el subárbol izquierdo.
        if (key < root->key)
            root->left = remove(root->left, key);

        // Si la clave a eliminar es mayor que la clave del nodo actual,
        // entonces debe estar en el subárbol derecho.
        else if (key > root->key)
            root->right = remove(root->right, key);

        // Si la clave a eliminar es igual a la clave del nodo actual, entonces
        // este es el nodo que se eliminará.
        else {
            // Nodo con solo un hijo o sin hijos
            if ((root->left == nullptr) || (root->right == nullptr)) {
                AVL* temp = root->left ? root->left : root->right;

                // Caso sin hijos
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else // Caso con un hijo
                    *root = *temp; // Copia el contenido del hijo no nulo

                delete temp;
            } else {
                // Nodo con dos hijos: obtener el sucesor in-order (menor valor en el subárbol derecho)
                AVL* temp = minValueNode(root->right);

                // Copia el sucesor in-order en el nodo actual
                root->key = temp->key;

                // Elimina el sucesor in-order
                root->right = remove(root->right, temp->key);
            }
        }

        // Si el árbol tenía solo un nodo, entonces no es necesario balancearlo
        if (root == nullptr)
            return root;

        // Actualizar la altura del nodo actual
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        // Obtener el factor de equilibrio del nodo actual para verificar si se ha desequilibrado
        int balance = getBalance(root);

        // Casos de desequilibrio:

        // Izquierda izquierda
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        // Izquierda derecha
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Derecha derecha
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        // Derecha izquierda
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // Método auxiliar para encontrar el nodo con el valor mínimo en un árbol
    AVL* minValueNode(AVL* node) {
        AVL* current = node;

        // Recorre el árbol hasta encontrar el nodo más a la izquierda
        while (current->left != nullptr)
            current = current->left;

        return current;
    }
};

#endif //FILE_SYSTEM_MANAGEMENT_DATA_STRUCTURE_2024A_AVL_TREE_H
