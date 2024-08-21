#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cstring>

#include "conexion.h"

using namespace std;

#define PUERTO 5005
#define SALIR "/salir"

/// USUARIO
void generarUsuario(SOCKET ClientSocket, char menu[150], char buffer[1024]){
    printf("Longitud seleccionada %s\n", buffer); // CONSOLA SERVER
    int longitud = atoi(buffer);

    if(longitud > 5 && longitud < 15){
        const string vocales = "aeiou";
        const string consonantes = "bcdfghjklmnpqrstvwxyz";
        srand(static_cast<unsigned int>(time(nullptr)));

        bool empezarConVocal = rand() % 2 == 0;

        string usuario;
        bool esVocal = empezarConVocal;

        for (int i = 0; i < longitud; ++i) {
            if (esVocal) {
                usuario += vocales[rand() % vocales.size()];
            } else {
                usuario += consonantes[rand() % consonantes.size()];
            }
                esVocal = !esVocal;
        }

        string mensajeString = "El usuario generado es " + usuario + "\n" + menu;

        char mensaje[200];
        strncpy(mensaje, mensajeString.c_str(), sizeof(mensaje) - 1);
        mensaje[sizeof(mensaje) - 1] = '\0';
        send(ClientSocket, mensaje , 200, 0);

    } else {
        char mensaje2[200] = "La longitud para generar el usuario es incorrecta";
        strcat(mensaje2, menu);
        send(ClientSocket, mensaje2, 200, 0);
    }
}

/// CLAVE
void generarClave(SOCKET ClientSocket, char menu[150], char buffer[1024]){
    printf("Longitud seleccionada %s\n", buffer); // CONSOLA SERVER
    int longitud = atoi(buffer);

    if(longitud > 5 && longitud < 15){
        const string vocales = "aeiou";
        const string consonantes = "bcdfghjklmnpqrstvwxyz";
        const string vocalesM = "AEIOU";
        const string consonantesM = "BCDFGHJKLMNPQRSTYWXYZ";
        const string numeros = "0123456789";
        srand(static_cast<unsigned int>(time(nullptr)));

        int tipoCaracter = rand() % 5;

        string clave;

        for (int i = 0; i < longitud; ++i) {
            switch(tipoCaracter){
                case 0:
                    clave += vocales[rand() % vocales.size()];
                    break;
                case 1:
                    clave += consonantes[rand() % consonantes.size()];
                    break;
                case 2:
                    clave += vocalesM[rand() % vocalesM.size()];
                    break;
                case 3:
                    clave += consonantesM[rand() % consonantesM.size()];
                    break;
                case 4:
                    clave += numeros[rand() % numeros.size()];
                    break;
            }
            tipoCaracter = rand() % 5;
        }

        string mensajeString = "La clave generada es " + clave + "\n" + menu;

        char mensaje[200];
        strncpy(mensaje, mensajeString.c_str(), sizeof(mensaje) - 1);
        mensaje[sizeof(mensaje) - 1] = '\0';
        send(ClientSocket, mensaje , 200, 0);

    } else {
        char mensaje2[200] = "La longitud para generar la clave es incorrecta";
        strcat(mensaje2, menu);
        send(ClientSocket, mensaje2, 200, 0);
    }
}

int main()
{
    // INICIALIZAMOS WINSOCK
    WSADATA wsaData;
    inicializarWinsock(wsaData);

    // CREAMOS SOCKET
    SOCKET serverSocket = crearSocket();

    // DEFINIMOS PUERTOS Y PROTOCOLOS
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PUERTO);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // BINDEAMOS SOCKET
    bindeoSocket(serverSocket,serverAddr);

    // LISTEN SOCKET
    listenSocket(serverSocket);

    // VARIABLES
    SOCKET ClientSocket;

    // MENU
    char menuConsulta[] = "\n1. Usuario \n2. Clave\n";
    char menu[200];
    bool primeraVez = true;

    while (1) {
        if(primeraVez){
            // ACEPTAMOS LA CONEXION
            ClientSocket = acceptClient(serverSocket);
            strcpy(menu,menuConsulta);
            send(ClientSocket, menu, strlen(menu), 0);
            primeraVez = false;
        }

        // RECIBIMOS LA RESPUESTA DEL CLIENTE
        char buffer[1024];
        int bytesRecibidos = recv(ClientSocket, buffer, sizeof(buffer), 0);

        // SE PROCESA PARA QUE ENTRE AL SWITCH Y SE IMPRIME EN CONSOLA
        int opcion = atoi(buffer);
        printf("Opcion seleccionada %d\n", opcion);

        switch (opcion) {
            /// -------------------------------------USUARIO----------------------------------------
            case 1:{
                // SE LE PREGUNTA AL CLIENTE LA LONGITUD DEL USUARIO
                char respuesta1[] = "Seleccionaste opcion 1, ¿Cual es la longitud que desea generar? (/salir para volver)\n";
                send(ClientSocket, respuesta1, sizeof(respuesta1), 0);
                recv(ClientSocket, buffer, sizeof(buffer), 0);

                // /SALIR IMPLEMENTADO
                if(strcmp(buffer,SALIR) == 0){
                    send(ClientSocket, menu, strlen(menu), 0);
                    break;
                }

                // GENERAMOS USUARIO
                generarUsuario(ClientSocket,menu,buffer);

                break;
            }
            /// --------------------------------------CLAVE------------------------------------------
            case 2:{
                // SE LE PREGUNTA AL CLIENTE LA LONGITUD TRADUCCION DE LA CLAVE
                char respuesta2[] = "Seleccionaste opcion 2 ¿Cual es la longitud que desea generar? (/salir para volver)\n";
                send(ClientSocket, respuesta2, sizeof(respuesta2), 0);
                fflush(stdin);
                recv(ClientSocket, buffer, sizeof(buffer), 0);

                // /SALIR IMPLEMENTADO
                if(strcmp(buffer,SALIR) == 0){
                    send(ClientSocket, menu, strlen(menu), 0);
                    break;
                }

                // GENERAMOS CLAVE
                generarClave(ClientSocket, menu, buffer);

                break;
            }
            default:{
                printf("Opcion incorrecta - Cerrando conexion\n");
                closesocket(ClientSocket);
                primeraVez = true;
                break;
            }
        }
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
