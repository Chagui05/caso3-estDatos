#ifndef INCLUDED_HTTP_TCPSERVER_LINUX
#define INCLUDED_HTTP_TCPSERVER_LINUX

#include <stdio.h>
#include <winsock.h>
#include <stdlib.h>
#include <string>

namespace http
{
    class TcpServer
    {
    public:
        TcpServer(std::string ip_adress, int port);
        ~TcpServer();
    private:
        std::string m_ip_address;
        int m_port;
        SOCKET m_socket;
        SOCKET m_new_socket;
        long m_incommingMessage;
        struct sockaddr_in m_socketAdress;
        int m_socketAddress_len;
        std::string m_serverMessage;
        WSADATA m_wsaData;

        int startServer();
        void closeServer();
    };
} // namespace http

#endif