#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include "arreglo.h"
#include "pila.h"
#include "cola.h"
#include "avl_tree.h"

enum class NodeType { File, Directory }; // Enumeración para representar el tipo de nodo: Archivo o Directorio
static int idIncremental = 1; // Variable estática para mantener un ID incremental para los nodos

class FileNode {
private: 
    int id; // ID del nodo
    std::string name; // Nombre del nodo
    NodeType type; // Tipo del nodo (Archivo o Directorio)
    std::string content = ""; // Contenido del archivo (solo válido si el nodo es un archivo)
    arreglo_lista<FileNode*> children; // Arreglo dinámico para almacenar los hijos del nodo (archivos o directorios)
    pila<FileNode*> children_pila; // Pila para almacenar los hijos del nodo (archivos o directorios)
    cola<FileNode*> children_cola; // Cola para almacenar los hijos del nodo (archivos o directorios)
    FileNode* parent = nullptr; // Puntero al nodo padre (null si es el nodo raíz)

public:
    // Constructor: Crea un nuevo nodo con el nombre y tipo especificados
    FileNode(std::string name, NodeType type) : name{name}, type{type} { id = idIncremental++; }

    // Método para obtener el ID del nodo
    int getId() { return id; }

    // Método para obtener el nombre del nodo
    std::string getName() const { return name; }

    // Método para obtener el tipo del nodo (Archivo o Directorio)
    NodeType getType() const { return type; }

    // Método para ordenar los nodos hijos por nombre
    void sortChildrenByName() {
        std::sort(children.begin(), children.end(), [](FileNode* a, FileNode* b) {
            return a->getName() < b->getName();
        });
    }

    void sortDataQuick(const int& leftEdge, const int& rightEdge, arreglo_lista<FileNode*>&data){
        // Criterio de paro
        if(leftEdge>= rightEdge){
            return;
        }

        // Separación
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

        // Llamadas recursivas
        sortDataQuick(leftEdge, i-1,data);
        sortDataQuick(i+1, rightEdge,data);
    }
    // Método para obtener los hijos del nodo como un arreglo
    arreglo_lista<FileNode*>& getChildren() { return children; }

    // Método para obtener los hijos del nodo como una pila
    const pila<FileNode*>& getChildrenPila() const { return children_pila; }

    // Método para obtener los hijos del nodo como una cola
    const cola<FileNode*>& getChildrenCola() const { return children_cola; }

    // Método para obtener el nodo padre
    FileNode* getParent() const { return parent; }

    // Método para establecer el nodo padre
    void setParent(FileNode* parent) { this->parent = parent; }

    // Método para agregar un hijo al nodo
    void addChild(FileNode* child) {
        child->setParent(this); // Establecer este nodo como el padre del hijo
        children_cola.encolar(child); // Agregar el hijo a la cola de nodos hijos
        children.push_final(child); // Agregar el hijo al arreglo de nodos hijos
        children_pila.push(child); // Agregar el hijo a la pila de nodos hijos
    }

    // Método para eliminar un hijo del nodo por su nombre
    bool deleteChild(std::string name) {
        for (int i = 0; i < children.size(); i++) {
            if (children[i]->getName() == name) {
                // Eliminar el hijo del arreglo de nodos hijos
                delete children[i];
                children.pop(i);
                return true;
            }
        }
        return false; // Devolver falso si el hijo no se encuentra
    }

    // Método para eliminar un elemento de la pila
    void deleteFromPila(FileNode* nodeToDelete) {
        pila<FileNode*> tempPila; // Crear una pila temporal para almacenar los elementos de la pila original
        while (!children_pila.vacia()) {
            FileNode* topNode = children_pila.tope(); // Obtener el elemento superior de la pila original
            children_pila.pop(); // Eliminar el elemento superior de la pila original
            if (topNode != nodeToDelete) {
                tempPila.push(topNode); // Agregar el elemento superior a la pila temporal si no es el nodo a eliminar
            }
        }
        while (!tempPila.vacia()) {
            FileNode* topNode = tempPila.tope(); // Obtener el elemento superior de la pila temporal
            tempPila.pop(); // Eliminar el elemento superior de la pila temporal
            children_pila.push(topNode); // Agregar el elemento superior a la pila original
        }
    }

    // Método para realizar una búsqueda en profundidad (DFS) de un nodo por su nombre
    FileNode* dfs(std::string name) {
        if (this->name == name) // Si el nombre coincide con el nodo actual, devolver este nodo
            return this;
        for (int i = 0; i < children.size(); i++) {
            // Realizar una búsqueda en profundidad en cada hijo (si es un directorio)
            if (children[i]->getType() == NodeType::Directory) {
                FileNode* ans = children[i]->dfs(name);
                if (ans != nullptr)
                    return ans; // Devolver el nodo si se encuentra
            }
            // Si el nombre coincide con el de algún hijo, devolver ese hijo
            if (children[i]->getName() == name)
                return children[i];
        }
        return nullptr; // Devolver nulo si el nodo no se encuentra
    }

    FileNode* dfs(int id){
        if(this->getId() == id){
            return this;
        }
        for(int i = 0; i < children.size(); i++){
            
            if(children[i]->getType() == NodeType::Directory){
                FileNode* ans = children[i]->dfs(id);
                if(ans != nullptr){
                    return ans;
                }

                if(children[i]->getId() == id){
                    return children[i];
                }   
            }
        }
        return nullptr;
    }

    // Método para establecer el contenido del nodo (solo válido si el nodo es un archivo)
    void setContent(std::string newContent) {
        content = newContent;
    }

    // Método para obtener el contenido del nodo (solo válido si el nodo es un archivo)
    std::string getContent() {
        return content;
    }

    // Método para realizar una búsqueda binaria de un nodo por su ID en el arreglo de nodos hijos
    FileNode* busquedaBinariaChildrenId(arreglo_lista<FileNode*>& children, int id_a_encontrar, int abajo, int arriba) {
        if (abajo > arriba) {
            return nullptr;
        }
        int medio = abajo + (arriba - abajo) / 2;
        if (children[medio]->getId() == id_a_encontrar) {
            return children[medio];
        }
        else if (children[medio]->getId() > id_a_encontrar) {
            return busquedaBinariaChildrenId(children, id_a_encontrar, abajo, medio - 1);
        }
        else {
            return busquedaBinariaChildrenId(children, id_a_encontrar, medio + 1, arriba);
        }
    }

    // Destructor: Liberar la memoria asignada para los nodos hijos
    ~FileNode() {
        for (int i = 0; i < children.size(); i++)
            delete children[i];
    }
};

class Directory {
private:
    FileNode* root; // Puntero al nodo raíz del directorio
    FileNode* currentDirectory; // Puntero al nodo que representa el directorio actual
    AVL* arbol = nullptr;

public:
    // Constructor: Crear un nuevo directorio con un nodo raíz predeterminado
    Directory() {
        root = new FileNode("root", NodeType::Directory);
        currentDirectory = root; // Al inicio, el directorio actual es el directorio raíz
        arbol = new AVL(0);
    }

    // Destructor: Liberar la memoria asignada para el nodo raíz
    ~Directory() {
        delete root;
    }

    // Método para obtener el nodo raíz del directorio
    FileNode* getRoot() const { return root; }

    // Método para obtener el nodo que representa el directorio actual
    FileNode* getCurrentDirectory() const { return currentDirectory; }

    // Método para establecer el nodo que representa el directorio actual por su nombre
    void setCurrentDirectory(std::string name) {
        if (name == "..") {
            goToParentDirectory(); // Moverse al directorio padre
            return;
        } else if (name == "/") {
            currentDirectory = root; // Moverse al directorio raíz
            return;
        }
        FileNode* toReach = currentDirectory->dfs(name); // Buscar el directorio
        if (toReach == nullptr) {
            std::cout << "No se encontró el directorio." << std::endl;
            return;
        }
        currentDirectory = toReach ;
    }

    // Método para establecer el nodo que representa el directorio actual
    void setCurrentDirectoryInAll(FileNode* node){
        currentDirectory = node;
    }

    // Método para moverse al directorio padre
    void goToParentDirectory() {
        if (currentDirectory->getParent() != nullptr) {
            currentDirectory = currentDirectory->getParent();
        } else {
            std::cout << "No hay directorio anterior." << std::endl;
        }
    }

    // Método para buscar un nodo por su nombre en todos los directorios
    FileNode* findNodeInAll(std::string name) {
        return root->dfs(name);
    }

    // Método para buscar un nodo por su ID en todos los directorios
    FileNode* findNodeInAll(int id){
        return root->dfs(id);
    }

    // Método para buscar un nodo por su nombre en el directorio actual
    FileNode* findNode(std::string name) {
        return currentDirectory->dfs(name);
    }

    // Método para buscar un nodo por su ID en el directorio actual
    FileNode* findNode(int id){
        return currentDirectory->dfs(id);
    }

    // Método para buscar un nodo por su ID en el directorio actual
    FileNode* findNodeById(int id) {
        currentDirectory->sortDataQuick(0, currentDirectory->getChildren().size() - 1, currentDirectory->getChildren());
        return currentDirectory->busquedaBinariaChildrenId(currentDirectory->getChildren(), id, 0, currentDirectory->getChildren().size() - 1);
    }

    bool searchInArbol(int id){
        return arbol->search(id);
    }

    // Método para crear un nuevo archivo en el directorio actual
    void createFile(std::string name) {
        FileNode* newNode = new FileNode(name, NodeType::File);
        currentDirectory->addChild(newNode);
        arbol = arbol->insert(arbol, newNode->getId());
    }

    // Método para crear un nuevo directorio en el directorio actual
    void createDirectory(std::string name) {
        FileNode* newNode = new FileNode(name, NodeType::Directory);
        currentDirectory->addChild(newNode);
        arbol = arbol->insert(arbol, newNode->getId());
    }

    // Método para establecer el contenido de un archivo en el directorio actual
    void setContent(std::string fileName, std::string newContent) {
        arreglo_lista<FileNode*> children = currentDirectory->getChildren();
        for (int i = 0; i < children.size(); i++) {
            if(children[i]->getName() == fileName && children[i]->getType() == NodeType::File){
                children[i]->setContent(newContent);
                return;
            }
        }
    }

    // Método para obtener el contenido de un archivo en el directorio actual
    std::string getContent(std::string fileName) {
        arreglo_lista<FileNode*> children = currentDirectory->getChildren();
        for (int i = 0; i < children.size(); i++) {
            if(children[i]->getName() == fileName && children[i]->getType() == NodeType::File){
                return children[i]->getContent();
            }
        }
        return "noSeEncontro";
    }

    

    // Método para obtener y mostrar todos los archivos y directorios en el directorio actual
    void getAll() {
        arreglo_lista<FileNode*> children = currentDirectory->getChildren(); // Obtener los hijos del directorio actual

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

    // Método para obtener y mostrar todos los archivos y directorios en el directorio actual, en orden inverso de creación
    void getAllLastest(){
        pila<FileNode*> childrenPila = currentDirectory->getChildrenPila(); // Obtener los hijos del directorio actual en una pila

        // Colas para almacenar nombres de archivos y directorios
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

    // Método para obtener y mostrar todos los archivos y directorios en el directorio actual, en orden de creación
    void getAllOldest(){
        cola<FileNode*> childrenCola = currentDirectory->getChildrenCola(); // Obtener los hijos del directorio actual en una cola

        // Colas para almacenar nombres de archivos y directorios
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

    // Método para obtener y mostrar todos los archivos y directorios en el directorio actual, ordenados por nombre
    void getAllByName(){
        currentDirectory->sortChildrenByName();
        arreglo_lista<FileNode*> children = currentDirectory->getChildren(); // Obtener los hijos del directorio actual
        for(int i = 0 ; i < children.size(); i++){
            if(children[i]->getType() == NodeType::File){
                std::cout << "[File] " << children[i]->getName() << std::endl;
            }else{
                std::cout << "[Directory] " << children[i]->getName() << std::endl;
            }
        }
    }


    // Método para obtener y mostrar todos los archivos y directorios en el directorio actual, ordenados por ID
    void getAllById(){
        currentDirectory->sortDataQuick(0, currentDirectory->getChildren().size() - 1, currentDirectory->getChildren());
        arreglo_lista<FileNode*> children = currentDirectory->getChildren(); // Obtener los hijos del directorio actual
        for(int i = 0 ; i < children.size(); i++){
            if(children[i]->getType() == NodeType::File){
                std::cout << children[i]->getId() <<" [File] " << children[i]->getName() << std::endl;
            }else{
                std::cout << children[i]->getId() << " [Directory] " << children[i]->getName() << std::endl;
            }
        }
    }


    // Método para eliminar un nodo del directorio actual por su nombre
    bool deleteNode(std::string name) {
        
        FileNode* nodeToDelete = currentDirectory->dfs(name); // Buscar el nodo a eliminar

        if (currentDirectory->deleteChild(name)) {
            arbol = arbol->remove(arbol, nodeToDelete->getId());
            return true;
        } else {
            return false;
        }
    }



    void deleteInArbol(int id){
        arbol = arbol->remove(arbol, id);
    }


    
};

#endif /* DIRECTORY_H */
