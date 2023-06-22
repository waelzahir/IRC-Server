#ifndef SERVER_HPP
#define SERVER_HPP
#include "includes.hpp"
#include "Client.hpp"


class  Server
{
    public:
        Server();
        void    init(char   *arg);
        void    GetPort(std::string port);
        void    getPassword(std::string password);
        void    ServerBind();
        void    start();
        void    FdKill();
        void    IncomingRequest(int     incoming);
        void    RequestQueue();
        void    RequestHandler(int i);
        void    NewConection();
        void    ConectionClosed(int i);
        ~Server();
    private:
        int     port;
        std::vector<struct pollfd> polll;
        std::vector<Client *> clients;
        std::queue <std::pair <std::string , Client*> > RequestsQueue;
};
#endif

