#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "string"

#include "conexion.h"

using namespace std;

#define PUERTO 5005

int main()
{
    // INICIALIZAMOS WINSOCK
    WSADATA wsaData;
    inicializarWinsock(wsaData);

    // CREAMOS SOCKET
    SOCKET clientSocket = crearSocket();

    // DEFINIMOS PUERTO E IP
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PUERTO);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // CONECTAMOS CON EL SERVER
    connectSocket(clientSocket,serverAddr);
    while (1) {
        // LIMPIO CONSOLA
        system("cls");

        // RECIBIMOS EL MENSAJE / MENU DEL SERVIDOR
        char buffer[3200];
        int bytesRecibidos = recv(clientSocket, buffer, sizeof(buffer), 0);
        printf("\nMensaje recibido:\n%s", buffer);

        // SI NO LLEGA NIGNGUN MENSAJE CERRAMOS DEL LADO DEL CLIENTE
        if (bytesRecibidos <= 0) {
            printf("\n\n-----------------CONEXION CERRADA-----------------\n\n");
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }

        // SOLICITAMOS POR CONSOLA UNA SELECCION
        printf("\nIngrese el número de opción deseada: ");
        char seleccion[30];
        fflush(stdin);
        scanf("%30s", seleccion);

        // ENVIAMOS ESA SELECCION AL SERVIDOR
        send(clientSocket, seleccion, sizeof(seleccion), 0);

    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}

