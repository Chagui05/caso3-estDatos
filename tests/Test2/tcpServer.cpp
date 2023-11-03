#define _WINSTOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib "ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <string>

int main(){
    std::cout<<"Attempting to create server";

    SOCKET wsocket;
    SOCKET new_socket;
    WSADATA wsaData;
    struct sockaddr_in server;
    int server_len;
    int BUFFER_SIZE = 37020;
    //Inicializar
    if (WSAStartup(MAKEWORD(2,2), &wsaData)!=0){
        std::cout<<"Could not initialize"<<std::endl;
        return 0;
    }
    //Inicializar socket
    wsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (wsocket == INVALID_SOCKET){
        std::cout<<"Could not create socket"<<std::endl;
    }
}