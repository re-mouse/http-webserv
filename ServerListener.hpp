#ifndef SERVERLISTENER_CPP
#define SERVERLISTENER_CPP

#include <list>
#include "Server.hpp"
#include "sys/stat.h"

class ServerListener
{
    public:
        ServerListener(const int port);
        ~ServerListener();
        ServerListener operator=(ServerListener&);
        void ProcessConnectionToServer(sockaddr_in client_addr, int client_socket);
        int getPort();
        bool Intialize(); //Привязывается
        void StartListen(); //Начинает прослушивать свой порт
        bool BindServer(Server& server); //Добавляет сервер в лист, на который может быть отправлено соединение
    private:
        int sock;
        const int port;
        static void printLog(sockaddr_in client_addr, const string &message);
        Server &FindServerByHost(std::string host);
        ServerListener();
        std::list<Server> servers;
};

#endif