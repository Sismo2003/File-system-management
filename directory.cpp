#include <bits/stdc++.h>
#include "arreglo.h"

using namespace std;


enum class NodeType { File, Directory };

class FileNode{

    private:

        string name;
        NodeType type;
        arreglo_lista<FileNode*> children;
        // string content = contenido del nodo;
        FileNode* parent = nullptr;

    public:
        // FileNode(string name, NodeType type, FileNode* parent) : name{name}, type{type}, parent{parent} {}  // constructor en caso de que se inicialize con el padre 
        FileNode(string name, NodeType type) : name{name} , type{type} {
            if(type == NodeType::Directory){

            }
        }

        string getName() const { return name; }
        NodeType getType() const { return type; }
        const arreglo_lista<FileNode*>& getChildren() const { return children; }
        FileNode* getParent() const { return parent; }
        void setParent(FileNode* parent) { this->parent = parent; }
        void addChild(FileNode* child) { 
            child->setParent(this);  // se asigna el padre al hijo
            children.push_final(child); // se agrega el hijo a la lista de hijos
        }

        FileNode* dfs(string name){ // metodo de busqueda en profundidad
            if(this->name == name)
                return this;
            for(int i = 0; i < children.size(); i++){
                if(children[i]->getType() == NodeType::Directory){ // si es un directorio invocar dfs
                    FileNode* res = children[i]->dfs(name);
                    
                }
                if(children[i]->getName() == name) // si es un archivo y el nombre coincide, retornar el nodo
                    return children[i];
            }
            return nullptr; // si no se encuentra el nodo, retornar nullptr
        }

        ~FileNode(){
            for (int i = 0; i < children.size(); i++)
                delete children[i];
            delete parent;
        }

};



int main() {

    FileNode* rootNode = new FileNode("root", NodeType::Directory);
    FileNode* node1 = new FileNode("node1", NodeType::Directory);
    FileNode* file1 = new FileNode("file1", NodeType::File);
    FileNode* file2 = new FileNode("file2", NodeType::File);
    node1->addChild(file1);
    rootNode->addChild(node1);
    rootNode->addChild(file2);
    arreglo_lista<FileNode*> children = rootNode->getChildren();
    for( int i = 0; i < children.size(); i++)
        cout << children[i]->getName() << endl;


    

    cout << "Padre de node1: " << node1->getParent()->getName() <<endl;
    


    return EXIT_SUCCESS;
}