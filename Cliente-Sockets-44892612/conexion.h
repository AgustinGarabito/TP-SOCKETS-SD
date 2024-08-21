#ifndef CONEXION_H_INCLUDED
#define CONEXION_H_INCLUDED

#include <ws2tcpip.h>
#include <winsock2.h>

// INICIALIZAMOS WINSOCK
int inicializarWinsock(WSADATA wsaData);

// CREAMOS SOCKET
SOCKET crearSocket();

// CONECTAMOS SOCKET
int connectSocket(SOCKET clientSocket, sockaddr_in serverAddr);

#endif // CONEXION_H_INCLUDED
