#include <bits/stdc++.h>   // Incluye todas las bibliotecas estándar de C++
#include "directory.h"     // Incluye un archivo de cabecera personalizado

using namespace std;       // Usa el espacio de nombres estándar de C++

#define enl "\n"           // Macro para representar un salto de línea

#ifdef _WIN32              // Comprueba si se está compilando en Windows
#include<windows.h>        // Incluye la biblioteca windows.h para manipulación de la consola
#endif

void cls(){                // Definición de la función para limpiar la pantalla de la consola
#ifdef _WIN32              // Comprueba si se está compilando en Windows
    system("cls");         // Limpia la pantalla utilizando el comando cls de Windows
#else
    system("clear");       // Limpia la pantalla utilizando el comando clear en sistemas tipo Unix
#endif
}


vector<string> explode(string val, char delim ){ // Definición de la función explode que toma una cadena y un delimitador
    vector<string> result; // Vector que almacenará las subcadenas separadas
    string temp_result = ""; // Cadena temporal para construir cada subcadena
    bool flag = false; // Bandera para indicar si se encontró el delimitador en la cadena

    // Iteración a través de cada carácter de la cadena de entrada
    for(auto e : val){
        if(e != delim){ // Si el carácter actual no es el delimitador
            temp_result += e; // Agrega el carácter actual a la subcadena temporal
        }else{ // Si se encuentra el delimitador
            result.push_back(temp_result); // Agrega la subcadena temporal al vector de resultados
            temp_result = ""; // Reinicia la subcadena temporal para construir la siguiente subcadena
        }
    }
    result.push_back(temp_result); // Agrega la última subcadena (sin delimitador) al vector de resultados
    return result; // Devuelve el vector de subcadenas separadas
};


void newDirectory(Directory* actualDir, string userAnswer, NodeType type){
    try{
        // Intenta crear un nuevo directorio o archivo dependiendo del tipo especificado
        if(type == NodeType::Directory)
            actualDir->createDirectory(userAnswer); // Llama al método createDirectory del objeto actualDir
        else
            actualDir->createFile(userAnswer); // Llama al método createFile del objeto actualDir

    } catch (const exception& e) { // Captura cualquier excepción lanzada durante la ejecución del bloque try
        cout << "Error during newDirectory function: " << e.what() << enl; // Muestra un mensaje de error con la descripción de la excepción
    }
    cls(); // Llama a la función cls para limpiar la pantalla de la consola
}


void printMenu(){
    // Muestra un mensaje de bienvenida al sistema de archivos virtuales
    cout << "Bienvenido al Sistema de Archivos Virtuales" << enl;

    // Muestra los comandos disponibles
    cout << "Commandos Disponibles: " << enl;
    cout << "* dir + (Directorio) -> Crea un Nuevo directorio." << enl;
    cout << "* touch + (Archivo)  -> Crea un Nuevo Archivo." << enl;
    cout << "* delete + (Archivo o Directorio)  -> Elimina un Archivo o Directorio." << enl;
    cout << "* nano + (Archivo)   -> Editar un Archivo." << enl;
    cout << "* cd + (Directorio)  -> Cambia de directorio." << enl;
    cout << "* cd ..              -> Directorio anterior." << enl;
    cout << "* cd /               -> Directorio raiz." << enl;
    cout << "* ls                 -> Lista del Contenido." << enl;
    cout << "* exit               -> Termina el Programa." << enl;

    // Muestra saltos de línea adicionales para mejorar la legibilidad
    cout << enl << enl;
}



void moveDirectory(Directory* actualDir, string userAnswer){
    cls(); // Limpia la pantalla de la consola
    printMenu(); // Imprime el menú de comandos disponibles

    // Comprueba el comando ingresado por el usuario
    if (userAnswer == "..") { // Si el usuario quiere retroceder al directorio padre
        actualDir->goToParentDirectory(); // Llama al método goToParentDirectory para moverse al directorio padre
    } else if (userAnswer == "/") { // Si el usuario quiere ir al directorio raíz
        actualDir->setCurrentDirectory("/"); // Llama al método setCurrentDirectory para moverse al directorio raíz
    } else {
        // Si el usuario especifica un nombre de directorio
        FileNode* destination = actualDir->findNode(userAnswer); // Busca el nodo con el nombre especificado

        if (destination == nullptr) { // Si no se encuentra el directorio especificado
            cout << "El directorio especificado no existe." << enl << endl; // Muestra un mensaje de error
            return; // Termina la función
        } else if (destination->getType() == NodeType::File) { // Si el destino es un archivo en lugar de un directorio
            cout << "No se puede acceder a un archivo como directorio." << enl << endl; // Muestra un mensaje de error
            return; // Termina la función
        }

        actualDir->setCurrentDirectory(userAnswer); // Llama al método setCurrentDirectory para moverse al directorio especificado
    }

    cls(); // Limpia la pantalla de la consola
    printMenu(); // Imprime el menú de comandos disponibles
}


string editFile(Directory* fileToEdit, string fileName, NodeType type) {
    if (fileToEdit == nullptr) { // Comprueba si el archivo a editar es nulo
        cout << "El archivo especificado no existe." << enl << endl; // Muestra un mensaje de error
    } else {
        string nuevoContenido; // Cadena para almacenar el nuevo contenido del archivo
        string existencia = fileToEdit->getContent(fileName); // Obtiene el contenido actual del archivo

        if (existencia == "noSeEncontro") { // Si no se encuentra el archivo especificado
            return "noSeEncontro"; // Retorna un mensaje indicando que no se encontró el archivo
        }

        cout << "\nContenido del archivo: "; // Muestra el contenido actual del archivo
        if (existencia == "") { // Si el contenido está vacío
            cout << "VACIO" << endl; // Muestra un mensaje indicando que el archivo está vacío
        } else {
            cout << existencia << endl; // Muestra el contenido del archivo
        }

        cout << "\nNuevo contenido: "; // Solicita al usuario que ingrese el nuevo contenido del archivo
        getline(cin, nuevoContenido); // Lee la nueva línea de contenido desde la entrada estándar
        fileToEdit->setContent(fileName, nuevoContenido); // Establece el nuevo contenido del archivo
    }
    return "exito"; // Retorna un mensaje indicando que la edición del archivo fue exitosa

    cls(); // Limpia la pantalla de la consola (código inalcanzable debido al return anterior)
    printMenu(); // Imprime el menú de comandos disponibles (código inalcanzable debido al return anterior)
}


void menu(){
    Directory dir; // Crea un objeto Directory llamado 'dir' para representar el sistema de archivos virtual
    string userAnswer; // Variable para almacenar la respuesta del usuario

    printMenu(); // Muestra el menú de comandos disponibles

    // Bucle principal que se ejecuta hasta que el usuario ingrese "exit"
    while (userAnswer != "exit") {
        cout << "~/"; // Muestra la ruta actual del directorio
        cout << dir.getCurrentDirectory()->getName() << ": "; // Muestra el nombre del directorio actual
        getline(cin, userAnswer); // Lee la respuesta del usuario

        auto vi_userAnswer = explode(userAnswer, ' '); // Divide la respuesta del usuario en palabras

        // Verifica si la cantidad de palabras en la respuesta del usuario es válida
        if (vi_userAnswer.size() <= 2) {
            // Lógica para ejecutar comandos según la respuesta del usuario
            if (vi_userAnswer[0] == "dir") { // Comando para crear un nuevo directorio
                if (vi_userAnswer.size() == 2) { // Verifica si se proporciona el nombre del directorio
                    newDirectory(&dir, vi_userAnswer[1], NodeType::Directory); // Llama a la función para crear un nuevo directorio
                    printMenu();
                    cout << "Directorio Creado con exito!" << enl << enl; // Muestra un mensaje de éxito
                } else {
                    cout << "Faltan parametros!" << enl << enl; // Muestra un mensaje de error si faltan parámetros
                }
            }
            // Lógica para otros comandos similares (touch, cd, ls, nano, exit, delete)
            else if (vi_userAnswer[0] == "touch") {
                // Logica para crear Archivo
                if (vi_userAnswer.size() == 2) {
                    newDirectory(&dir, vi_userAnswer[1], NodeType::File);
                    printMenu();
                    cout << "Archivo Creado con exito!" << enl << enl;
                } else {
                    cout << "Faltan parametros!" << enl;
                }
            } else if (vi_userAnswer[0] == "cd") {
                // Logica para Moverse de directorio.
                if (vi_userAnswer.size() == 2) {
                    moveDirectory(&dir, vi_userAnswer[1]);
                } else {
                    cout << "Faltan parametros!" << enl;
                }
            } else if (vi_userAnswer[0] == "ls") {
                // Logica para mostrar los directorios y archivos
                string option;
                cout << "Opcion 1: Mostrar por default\nOpcion 2: Mostrar de antiguo a nuevo\nOpcion 3: Mostrar de nuevo a antiguo\n" << enl;
                cout << "Ingrese una opcion: ";
                cin >> option;
                cin.ignore();
                if (option == "1") {
                    cls();
                    printMenu();
                    dir.getAll();
                    cout << enl;
                } else if (option == "2") {
                    cls();
                    printMenu();
                    dir.getAllOldest();
                    cout << enl;
                } else if (option == "3") {
                    cls();
                    printMenu();
                    dir.getAllLastest();
                    cout << enl;
                } else {
                    cls();
                    printMenu();
                    cout << "Opcion no valida!" << enl;
                }
            } else if (vi_userAnswer[0] == "nano") {
                // Logica para Moverse de directorio.
                if (vi_userAnswer.size() == 2) {
                    string result = editFile(&dir, vi_userAnswer[1], NodeType::File);
                    cls(); printMenu();
                    if (result == "noSeEncontro") { cout << "El archivo no se encontro!" << enl << enl; }
                    else { cout << "Archivo editado con exito!" << enl << enl; }
                } else {
                    cout << "Faltan parametros!" << enl;
                }
            } else if (vi_userAnswer[0] == "exit") {
                return; // Sale de la función y termina el programa
            } else if (vi_userAnswer[0] == "delete") {
                // Logica para eliminar directorio o archivo
                cls();
                if (vi_userAnswer.size() == 2) {
                    if (dir.deleteNode(vi_userAnswer[1])) {
                        printMenu();
                        cout << "Archivo o Directorio Eliminado con exito!" << enl << enl;
                    }
                } else {
                    cout << "Faltan parametros!" << enl;
                }
            } else {
                cls();
                printMenu();
                cout << "Comando Desconocido!" << enl;
            }
        } else {
            cls();
            printMenu();
            cout << "Parametros exedidos!" << enl;
        }
    }
}



int main(){
    menu(); // Llama a la función menu para iniciar el sistema de archivos virtual
    return 0; // Retorna 0 para indicar que el programa se ejecutó correctamente
}
