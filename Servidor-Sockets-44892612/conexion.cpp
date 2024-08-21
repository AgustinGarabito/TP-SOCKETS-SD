#include "conexion.h"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <string.h>

// INICIALIZAMOS WINSOCK
int inicializarWinsock(WSADATA wsaData){
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("Error al inicializar Winsock");
        return 1;
    }
    return 0;
}

// CREAMOS SOCKET
SOCKET crearSocket(){
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        perror("Error al crear el socket del servidor");
        return 1;
    }
    return serverSocket;
}



// BINDEAMOS SOCKET
int bindeoSocket(SOCKET serverSocket, sockaddr_in serverAddr){
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        perror("Error al enlazar el socket del servidor");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}


// LISTEN SOCKET
int listenSocket(SOCKET serverSocket){
    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        perror("Error al escuchar");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

// ACEPTAMOS LA CONEXION
SOCKET acceptClient(SOCKET serverSocket){
    SOCKET ClientSocket = accept(serverSocket, NULL, NULL);
    if(ClientSocket == INVALID_SOCKET){
        perror("Error al aceptar el socket del cliente");
        return 1;
    }

    return ClientSocket;
}
