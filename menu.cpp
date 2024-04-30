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
    actualDir->setCurrentDirectory(userAnswer);
    cls();
}

void menu(){
    Directory dir;
    string userAnswer;

    while (userAnswer != "exit"){
        cout<<"Bienvenido al Sistema de Archivos Virtuales"<<enl;
        cout<<"Dirrectorio Actual: "<<dir.getCurrentDirectory()->getName()<<enl;
        cout<<"Commandos Disponibles: "<<enl;
        cout<<"* dir + (Directorio) -> Crea un Nuevo directorio."<<enl;
        cout<<"* touch + (Archivo)  -> Crea un Nuevo Archivo."<<enl;
        cout<<"* cd + (Directorio)  -> Cambia de directorio."<<enl;
        cout<<"* ls                 -> Lista del Contenido."<<enl;
        cout<<"* exit               -> Termina el Programa."<<enl;
        cout<<enl<<enl;

        cout<<"~/"<<dir.getCurrentDirectory()->getName()<<": ";
        getline(cin,userAnswer);
        auto vi_userAnswer = explode(userAnswer, ' ');
        if(vi_userAnswer.size() <= 2){
            if(vi_userAnswer[0] == "dir"){  // logica para crear directorio
                newDirectory(&dir,vi_userAnswer[1], NodeType::Directory);
                cout<<"Directorio Creado con exito!"<<enl<<enl;
            }
            else if(vi_userAnswer[0] == "touch"){ // Logica para crear Archivo
                newDirectory(&dir,vi_userAnswer[1], NodeType::File);
                cout<<"Archivo Creado con exito!"<<enl<<enl;
            }
            else if(vi_userAnswer[0] == "cd"){ // Logica para Moverse de directorio.
                moveDirectory(&dir,vi_userAnswer[1]);
            }
            else if(vi_userAnswer[0] == "ls"){ // PENSAR UNA FORMA MEJOR DE MOSTRAR TODOS LOS DIRECTORIOS!
                cls();
                cout<<"TODO:" <<enl;dir.getAll();
            }
            else if(vi_userAnswer[0] == "exit"){
                return;
            }
            else{
                cout<<"Commando Desconocido!"<<enl;
            }
        }
        else{
            cout<<"Parametros exedidos!"<<enl;
        }

    }
}


int main(){
    menu();
    return 0;

}
