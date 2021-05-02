#ifndef SERVER_HPP
#define SERVER_HPP

#include "Config.hpp"
#include "Response.hpp"
#include "includes.hpp"

using namespace std;

class Server
{
    private:
        int socket_fd;
        std::string serverName;
        const Config serverConfig;
        Server();

    public:
        Server(const Config server_config);
        Server(Server const &rhs);
        Server &operator=(Server const &rhs);
        bool operator==(Server);
        ~Server();
        std::string GetServerName();
        void startServer();
        void closeServer();
        bool SendHttpResponse(const sockaddr_in &addr, const int sock, Http::Request *request);
        static void printLog(sockaddr_in client_addr, const string& message);
};

#endif