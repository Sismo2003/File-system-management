#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include "arreglo.h"

enum class NodeType { File, Directory };

class FileNode {
private:
    std::string name;
    NodeType type;
    std::string content = "";
    arreglo_lista<FileNode*> children;
    FileNode* parent = nullptr;

public:
    FileNode(std::string name, NodeType type) : name{name}, type{type} {}

    std::string getName() const { return name; }
    NodeType getType() const { return type; }
    const arreglo_lista<FileNode*>& getChildren() const { return children; }
    FileNode* getParent() const { return parent; }
    void setParent(FileNode* parent) { this->parent = parent; }
    void addChild(FileNode* child) {
        child->setParent(this);
        children.push_final(child);
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
        content = newContent;
    }

    std::string getContent() {
        return content;
    }

    ~FileNode() {
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
        return "";
    }

    void getAll() {
        arreglo_lista<FileNode*> children = currentDirectory->getChildren();
        for (int i = 0; i < children.size(); i++) {
            if(children[i]->getType() == NodeType::File){
                std::cout << "File: " << children[i]->getName() << std::endl;
            }else{
                std::cout << "Directory: " << children[i]->getName() << std::endl;
            }
        }
    }



};

#endif /* DIRECTORY_H */
