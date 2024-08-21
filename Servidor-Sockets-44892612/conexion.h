#ifndef CONEXION_H_INCLUDED
#define CONEXION_H_INCLUDED

#include <ws2tcpip.h>
#include <winsock2.h>

// INICIALIZAMOS WINSOCK
int inicializarWinsock(WSADATA wsaData);

// CREAMOS SOCKET
SOCKET crearSocket();

// BINDEAMOS SOCKET
int bindeoSocket(SOCKET serverSocket, sockaddr_in serverAddr);

// LISTEN SOCKET
int listenSocket(SOCKET serverSocket);

// ACEPTAR CONEXION
SOCKET acceptClient(SOCKET serverSocket);

#endif // CONEXION_H_INCLUDED
