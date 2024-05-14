#include <bits/stdc++.h>
// #include "directory.h"
#include "arreglo.h"
#include "avl_tree.h"


using namespace std;

int main(){
    AVL *root = new AVL(0);

    root->insert(5);
    root = root->insert(root, 10);
    root = root->insert(root, 20);
    root = root->insert(root, 30);
    root = root->insert(root, 40);
    root = root->insert(root, 50);
    root = root->insert(root, 25);
    root->insert(70);
    root->insert(60);


    root->preOrder(root);
    cout << endl;

    // root->remove(25);

    // root->preOrder(root);

    if(root->search(25))
        cout << "Found" << endl;
    else
        cout << "Not Found" << endl;


    root->remove(25);

    root->preOrder(root);

    cout << endl;

    if(root->search(25)){
        cout << "Found" << endl;
    }else{
        cout << "Not Found" << endl;
    }

    cout << endl;
    return EXIT_SUCCESS;
}
