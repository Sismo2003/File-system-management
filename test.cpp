#include <bits/stdc++.h>
#include "directory.h"
#include "arreglo.h"
#include "avl_tree.h"


using namespace std;

int main(){
    AVL *root = NULL;

    root = root->insert(root, 10);
    root = root->insert(root, 20);
    root = root->insert(root, 30);
    root = root->insert(root, 40);
    root = root->insert(root, 50);
    root = root->insert(root, 25);

    root->preOrder(root);


    return EXIT_SUCCESS;
}
