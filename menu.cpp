#include <bits/stdc++.h>
#include "directory.h"
using namespace std;
#define enl "\n"
#ifdef _WIN32
#include<windows.h>
#endif

void cls(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

vector<string> explode(string val, char delim ){
    vector<string> result;
    string temp_result = "";
    bool flag = false;
    for(auto e : val){
        if(e != delim){
            temp_result += e;
        }else{
            result.push_back(temp_result);
            temp_result = "";
        }
    }
    result.push_back(temp_result);
    return result;
};


void newDirectory(Directory* actualDir, string userAnswer,NodeType type){
    try{
        if(type == NodeType::Directory) actualDir->createDirectory(userAnswer);
        else actualDir->createFile(userAnswer);

    }catch (const exception& e){
        cout<<"Error during newDirectory function "<< e.what()<<enl;
    }
    cls();
}

void moveDirectory(Directory* actualDir, string userAnswer){
    if (userAnswer == "..") { // Retroceder al directorio padre
        actualDir->goToParentDirectory();
    } else if (userAnswer == "/") { // Ir al directorio ra�z
        actualDir->setCurrentDirectory("/");
    } else {
        FileNode* destination = actualDir->findNode(userAnswer); // Buscar el destino, implement� esto porque se pod�a acceder a un archivo como directorio y de esta forma se evita este error.

        if (destination->getType() == NodeType::File) {
            cout<<"No se puede acceder a un archivo como directorio."<<enl<< endl;
            return;
        }

        actualDir->setCurrentDirectory(userAnswer);
    }
    cls();
}

void printMenu(){
    cout<<"Bienvenido al Sistema de Archivos Virtuales"<<enl;
    //cout<<"Directorio Actual: "<<dir.getCurrentDirectory()->getName()<<enl;
    cout<<"Commandos Disponibles: "<<enl;
    cout<<"* dir + (Directorio) -> Crea un Nuevo directorio."<<enl;
    cout<<"* touch + (Archivo)  -> Crea un Nuevo Archivo."<<enl;
    cout<<"* cd + (Directorio)  -> Cambia de directorio."<<enl;
    cout<<"* cd ..              -> Directorio anterior."<<enl;
    cout<<"* cd /               -> Directorio raiz."<<enl;
    cout<<"* ls                 -> Lista del Contenido."<<enl;
    cout<<"* exit               -> Termina el Programa."<<enl;
    cout<<enl<<enl;
}

void menu(){
    Directory dir;
    string userAnswer;
    printMenu();

    while (userAnswer != "exit"){
        cout<<"~/"<<dir.getCurrentDirectory()->getName()<<": ";
        getline(cin,userAnswer);
        auto vi_userAnswer = explode(userAnswer, ' ');
        if(vi_userAnswer.size() <= 2){
            if(vi_userAnswer[0] == "dir"){  // logica para crear directorio
                if(vi_userAnswer.size() == 2) { //Agregu� est�s l�neas, "if(vi_userAnswer.size() == 2)", dentro de las respuestas del usuario para evitar que se cerrara la aplicaci�n
                    newDirectory(&dir, vi_userAnswer[1], NodeType::Directory);
                    printMenu();
                    cout << "Directorio Creado con exito!" << enl << enl;
                } else {
                    cout << "Faltan parametros!" << enl<<enl;
                }
            }
            else if(vi_userAnswer[0] == "touch"){ // Logica para crear Archivo
                if(vi_userAnswer.size() == 2) {
                    newDirectory(&dir, vi_userAnswer[1], NodeType::File);
                    printMenu();
                    cout << "Archivo Creado con exito!" << enl << enl;
                } else {
                    cout << "Faltan parametros!" << enl;
                }
            }
            else if(vi_userAnswer[0] == "cd"){ // Logica para Moverse de directorio.
                if(vi_userAnswer.size() == 2) {
                    moveDirectory(&dir, vi_userAnswer[1]);
                    cls();
                    printMenu();
                } else {
                    cout << "Faltan parametros!" << enl;
                }
            }
            else if(vi_userAnswer[0] == "ls"){ // Logica para mostrar los directorios y archivos
                cls();
                printMenu();
                cout<<enl;dir.getAll();
                cout<<enl;
            }
            else if(vi_userAnswer[0] == "exit"){
                return;
            }
            else{
                cls();
                printMenu();
                cout<<"Comando Desconocido!"<<enl;
            }
        }
        else{
            cls();
            printMenu();
            cout<<"Parametros exedidos!"<<enl;
        }

    }
}


int main(){
    menu();
    return 0;

}
