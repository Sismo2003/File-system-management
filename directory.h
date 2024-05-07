#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include "arreglo.h"
#include "pila.h"
#include "cola.h"

enum class NodeType { File, Directory };
static int idIncremental;

class FileNode {
private:
    int id;
    std::string name;
    NodeType type;
    std::string content = "";
    arreglo_lista<FileNode*> children;
    pila<FileNode*> children_pila;
    cola<FileNode*> children_cola;
    FileNode* parent = nullptr;

public:
    FileNode(std::string name, NodeType type) : name{name}, type{type}, id {idIncremental++} {} // Constructor

    int getId () { return id; }
    void setId (int nuevoId) { id = nuevoId; }
    std::string getName() const { return name; } // Getter for Name
    NodeType getType() const { return type; } // Getter for the type of the node
    const arreglo_lista<FileNode*>& getChildren() const { return children; } // Getter for the array of children's
    const pila<FileNode*>& getChildrenPila() const { return children_pila; } // Getter for the stack of children's
    const cola<FileNode*>& getChildrenCola() const { return children_cola; }   // Getter for the queue of children's
    FileNode* getParent() const { return parent; } // Getter for node parent
    void setParent(FileNode* parent) { this->parent = parent; } // Setter for the node parent
    void addChild(FileNode* child) { // Setter for the children's
        child->setParent(this); // set the parent of the child this node
        children_cola.encolar(child);   // push for the queue of nodes
        children.push_final(child); // push for the array of nodes
        children_pila.push(child); // push for the stack of nodes
    }

    bool deleteChild(std::string name) {
        for (int i = 0; i < children.size(); i++) {
            if (children[i]->getName() == name) {
                pila<FileNode*> children_pila_aux;
                cola<FileNode*> children_cola_aux;

                while(!children_cola.vacia()){
                    if(children_cola.frente_cola()->getName() == name){
                        children_cola.desencolar();
                    }else{
                        children_cola_aux.encolar(children_cola.frente_cola());
                        children_cola.desencolar();
                    }
                }

                children_cola = children_cola_aux;

                while(!children_cola_aux.vacia()){
                    children_pila_aux.push(children_cola_aux.frente_cola());
                    children_cola_aux.desencolar();
                }

                children_pila = children_pila_aux;

                delete children[i];
                children.pop(i);



                return true;
            }
        }
        return false;
    }

    FileNode* dfs(std::string name) {
        if (this->name == name)
            return this;
        for (int i = 0; i < children.size(); i++) {
            if (children[i]->getType() == NodeType::Directory) {
                FileNode* ans = children[i]->dfs(name);
                if (ans != nullptr)
                    return ans;
            }
            if (children[i]->getName() == name)
                return children[i];
        }
        return nullptr;
    }

    void setContent(std::string newContent) {
        content = newContent; // Setter for the content
    }

    std::string getContent() { // Getter for the content
        return content;
    }

    FileNode* busquedaBinariaChildrenId(arreglo_lista<FileNode*>& children, int id_a_encontrar, int abajo, int arriba) {
        if (abajo > arriba) {
            return nullptr;
        }

        int medio = abajo + (arriba - abajo) / 2;

        if (children[medio]->getId() == id_a_encontrar) {
            return children[medio];
        }
        else if (children[medio]->getId() > id) {
            return busquedaBinariaChildrenId(children, id_a_encontrar, abajo, medio - 1);
        }
        else {
            return busquedaBinariaChildrenId(children, id_a_encontrar, medio + 1, arriba);
        }
    }



    ~FileNode() { // Destructor
        for (int i = 0; i < children.size(); i++)
            delete children[i];
    }
};

class Directory {
private:
    FileNode* root;
    FileNode* currentDirectory; // Nodo que representa el directorio actual

public:
    Directory() {
        root = new FileNode("root", NodeType::Directory);
        currentDirectory = root; // Al inicio, el directorio actual es el directorio raíz
    }

    ~Directory() {
        delete root;
    }

    FileNode* getRoot() const { return root; }

    FileNode* getCurrentDirectory() const { return currentDirectory; }

    void setCurrentDirectory(std::string name) {
        if (name == "..") {
            goToParentDirectory(); // Llama a la función para moverse al directorio padre
            return;
        } else if (name == "/") {
            currentDirectory = root; // Mueve al directorio raíz
            return;
        }
        FileNode* toReach = currentDirectory->dfs(name); // Buscar el directorio
        if (toReach == nullptr) {
            std::cout << "No se encontró el directorio." << std::endl;
            return;
        }
        currentDirectory = toReach ;
    }

    void goToParentDirectory() {
        if (currentDirectory->getParent() != nullptr) {
            currentDirectory = currentDirectory->getParent(); // Regresar al directorio anterior
        } else {
            std::cout << "No hay directorio anterior." << std::endl;
        }
    }

    FileNode* findNodeInAll(std::string name) {
        return root->dfs(name); // Busca en todos los directorios
    }

    FileNode* findNode(std::string name) {
        return currentDirectory->dfs(name); // Busca en el directorio actual
    }

    void createFile(std::string name) {
        FileNode* newNode = new FileNode(name, NodeType::File);
        currentDirectory->addChild(newNode);
    }

    void createDirectory(std::string name) {
        FileNode* newNode = new FileNode(name, NodeType::Directory);
        currentDirectory->addChild(newNode);
    }



    void setContent(std::string fileName, std::string newContent) {
        arreglo_lista<FileNode*> children = currentDirectory->getChildren();
        for (int i = 0; i < children.size(); i++) {
            if(children[i]->getName() == fileName && children[i]->getType() == NodeType::File){
                children[i]->setContent(newContent);
                return;
            }
        }
    }

    std::string getContent(std::string fileName) {
        arreglo_lista<FileNode*> children = currentDirectory->getChildren();
        for (int i = 0; i < children.size(); i++) {
            if(children[i]->getName() == fileName && children[i]->getType() == NodeType::File){
                return children[i]->getContent();
            }
        }
        return "noSeEncontro";
    }

    void getAll() {
        arreglo_lista<FileNode*> children = currentDirectory->getChildren(); //Realicé cambios a getAll() para que se mostraran de mejor forma a la hora de usar ls.

        // Arreglos para almacenar nombres de archivos y directorios
        arreglo_lista<std::string> fileNames;
        arreglo_lista<std::string> directoryNames;

        // Separar los nombres de archivos y directorios
        for (int i = 0; i < children.size(); i++) {
            if (children[i]->getType() == NodeType::File) {
                fileNames.push_final(children[i]->getName());
            } else {
                directoryNames.push_final(children[i]->getName());
            }
        }

        // Imprimir archivos y directorios si existen
        if (fileNames.size() > 0 || directoryNames.size() > 0) {
            // Imprimir archivos
            for (int i = 0; i < fileNames.size(); i++) {
                std::cout << "[File] " << fileNames[i] << std::endl;
            }

            // Imprimir directorios
            for (int i = 0; i < directoryNames.size(); i++) {
                std::cout << "[Directory] " << directoryNames[i] << std::endl;
            }

            // Mostrar el número total de archivos y directorios
            std::cout << "Total de archivos: " << fileNames.size() << std::endl;
            std::cout << "Total de directorios: " << directoryNames.size() << std::endl;
        } else {
            // Si no hay archivos ni directorios, imprimir "Directorio vacío"
            std::cout << "Directorio vacio" << std::endl;
        }
    }

    void getAllLastest(){
        pila<FileNode*> childrenPila = currentDirectory->getChildrenPila(); //Realicé cambios a getAll() para que se mostraran de mejor forma a la hora de usar ls.

        // Arreglos para almacenar nombres de archivos y directorios
        cola<std::string> fileNames;
        cola<std::string> directoryNames;

        // Separar los nombres de archivos y directorios
        while(!childrenPila.vacia()){
            if (childrenPila.tope()->getType() == NodeType::File) {
                fileNames.encolar(childrenPila.tope()->getName());
                childrenPila.pop();
            } else {
                directoryNames.encolar(childrenPila.tope()->getName());
                childrenPila.pop();
            }
        }

        int totalFiles = fileNames.size();
        int totalDirectories = directoryNames.size();

        // Imprimir archivos y directorios si existen
        if (fileNames.size() > 0 || directoryNames.size() > 0) {
            // Imprimir archivos
            while(!fileNames.vacia()){
                std::cout << "[File] " << fileNames.frente_cola() << std::endl;
                fileNames.desencolar();
            }

            // Imprimir directorios
            while(!directoryNames.vacia()){
                std::cout << "[Directory] " << directoryNames.frente_cola() << std::endl;
                directoryNames.desencolar();
            }

            // Mostrar el número total de archivos y directorios
            std::cout << "Total de archivos: " << totalFiles << std::endl;
            std::cout << "Total de directorios: " << totalDirectories << std::endl;
        } else {
            // Si no hay archivos ni directorios, imprimir "Directorio vacío"
            std::cout << "Directorio vacio" << std::endl;
        }
    }

    void getAllOldest(){
        cola<FileNode*> childrenCola = currentDirectory->getChildrenCola(); //Realicé cambios a getAll() para que se mostraran de mejor forma a la hora de usar ls.

        // Arreglos para almacenar nombres de archivos y directorios
        cola<std::string> fileNames;
        cola<std::string> directoryNames;

        // Separar los nombres de archivos y directorios
        while(!childrenCola.vacia()){
            if (childrenCola.frente_cola()->getType() == NodeType::File) {
                fileNames.encolar(childrenCola.frente_cola()->getName());
                childrenCola.desencolar();
            } else {
                directoryNames.encolar(childrenCola.frente_cola()->getName());
                childrenCola.desencolar();
            }
        }

        int totalFiles = fileNames.size();
        int totalDirectories = directoryNames.size();

        // Imprimir archivos y directorios si existen
        if (fileNames.size() > 0 || directoryNames.size() > 0) {
            // Imprimir archivos
            while(!fileNames.vacia()){
                std::cout << "[File] " << fileNames.frente_cola() << std::endl;
                fileNames.desencolar();
            }

            // Imprimir directorios
            while(!directoryNames.vacia()){
                std::cout << "[Directory] " << directoryNames.frente_cola() << std::endl;
                directoryNames.desencolar();
            }

            // Mostrar el número total de archivos y directorios
            std::cout << "Total de archivos: " << totalFiles << std::endl;
            std::cout << "Total de directorios: " << totalDirectories << std::endl;
        } else {
            // Si no hay archivos ni directorios, imprimir "Directorio vacío"
            std::cout << "Directorio vacio" << std::endl;
        }

    }

    bool deleteNode(std::string name) {
        if (currentDirectory->deleteChild(name)) {
            return true;
        } else {
            return false;
        }
    }

    void sortDataQuick(const int& leftEdge, const int& rightEdge, arreglo_lista<FileNode*>&data){
        //criterio de paro
        if(leftEdge>= rightEdge){
            return;
        }

        //separacion
        int i=leftEdge;
        int j=rightEdge;

        while(i<j){
            while(i<j && data[i]->getId() <= data[rightEdge]->getId()){
                i++;
            }

            while(i<j && data[j]->getId() >= data[rightEdge]->getId()){
                j--;
            }

            if(i != j){
                std::swap(data[i],data[j]);
            }
        }

        if(i != rightEdge){
            std::swap(data[i],data[rightEdge]);
        }

        //llamadas recursivas
        sortDataQuick(leftEdge, i-1,data);
        sortDataQuick(i+1, rightEdge,data);

    }



};

#endif /* DIRECTORY_H */
