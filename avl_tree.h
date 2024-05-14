//
// Created by Alexis Ortiz ceceña on 09/05/24.
//

#ifndef FILE_SYSTEM_MANAGEMENT_DATA_STRUCTURE_2024A_AVL_TREE_H
#define FILE_SYSTEM_MANAGEMENT_DATA_STRUCTURE_2024A_AVL_TREE_H



// AVL tree implementation in C++



#include<bits/stdc++.h>
using namespace std;

class AVL
{
private:
    int key;         // Valor del nodo
    AVL *left;       // Puntero al hijo izquierdo
    AVL *right;      // Puntero al hijo derecho
    int height;      // Altura del nodo en el árbol

    // Constructor
    AVL(int k) : key(k), left(nullptr), right(nullptr), height(1) {}

    // Métodos públicos

    // Inserta un nodo en el árbol AVL
    void insert(int key)
    {
        root = insert(root, key);
    }

    // Realiza un recorrido en preorden del árbol
    void preOrder()
    {
        preOrder(root);
    }

public:
    AVL* root = nullptr;  // Puntero a la raíz del árbol

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
};




#endif //FILE_SYSTEM_MANAGEMENT_DATA_STRUCTURE_2024A_AVL_TREE_H
