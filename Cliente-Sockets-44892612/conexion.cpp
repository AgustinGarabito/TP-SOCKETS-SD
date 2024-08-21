#include "conexion.h"
#include <winsock2.h>
#include <ws2tcpip.h>

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
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        perror("Error al crear el socket del cliente");
        return 1;
    }
    return clientSocket;
}

// CONECTAMOS SOCKET
int connectSocket(SOCKET clientSocket, sockaddr_in serverAddr){
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        perror("Error al conectar al servidor");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}
