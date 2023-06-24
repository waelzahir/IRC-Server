/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:25:36 by ozahir            #+#    #+#             */
/*   Updated: 2023/06/24 00:16:42 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* public methods */

Server::~Server()
{
        while (clients.size())
    {
        // close(clients[0].socket);
        delete clients[0];
        clients.erase(clients.begin());
    }
    while (channels.size())
    {
        delete channels[0];
        channels.erase(channels.begin());
    }
}

Server::Server(std::string &pass, int port, int serial )
{
    if (pass.length() < 2)  
        throw "can't accept this password";
    this->password = pass;
    this->port = port;
    this->serverName = "Ircsrvr" + std::to_string(serial);
    this->createSocket();
    this->makeNonBlockSocket();
    this->makePortReusable();
    this->goBindSocket();
    if (listen(this->listensocket, 5) == -1)
    {
        close(this->listensocket);
        throw "listen error";
    }
    this->fds.push_back((struct pollfd){this->listensocket, POLLIN, 0});
}

void    Server::connect()
{
    /* only accepting clients here for now */
    int poll_num;

    poll_num = poll(&this->fds[0], this->fds.size(), 100);
    if (poll_num == 0)
        return ;
    this->getEvent(poll_num);
}


void    Server::disconect()
{
    /* deleting channels and */
    close(this->listensocket);
}



void    Server::createChannel(Channel *channel)
{
    this->channels.push_back(channel);
}



void    Server::removeChannel(Channel *channel)
{
   std::vector<Channel *>::iterator it = std::find(this->channels.begin(), this->channels.end(), channel);
   if (it != this->channels.end())
        this->channels.erase(it);
}


void    Server::addClient(Client *client)
{
    this->clients.push_back(client);
}





void    Server::removeClient(Client *client)
{
    std::vector<Client *>::iterator it = std::find(this->clients.begin(), this->clients.end(), client);
   if (it != this->clients.end())
        this->clients.erase(it);
}





void    Server::sendMessage(Message message) /* this method broadcast message to every client*/
{
    /**/
}








/* private methods */
void    Server::createSocket()
{
    this->listensocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->listensocket == -1)
        throw "error creating socket";
}
void    Server::makeNonBlockSocket()
{
    if (fcntl(this->listensocket, F_SETFL, O_NONBLOCK) == -1)
    {
        close(this->listensocket);
        throw "error fcntl";
    }
}
void    Server::makePortReusable()
{
    int flag = 1;
    if (setsockopt(this->listensocket, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) == -1)
    {
        close(this->listensocket);
        throw "setsockopt error";
    }
}
void    Server::goBindSocket()
{
    struct  sockaddr_in ad;
    bzero(&ad, sizeof (ad));
    ad.sin_family = AF_INET;
    ad.sin_addr.s_addr = inet_addr("0.0.0.0");
    ad.sin_port = htons(this->port);
    if (bind(this->listensocket, (struct sockaddr *)&ad, sizeof(ad))==-1)
    {
        close(this->listensocket);
        throw "bind error";
    }
}




void    Server::getEvent(int poll_num)
{
    if (fds[0].revents & 1)
        this->acceptNewClient();
}
void    Server::acceptNewClient()
{
    struct  sockaddr_in ad;
    bzero(&ad, sizeof(ad));
    socklen_t size = sizeof(ad);
    int fd = accept(this->fds[0].fd,(struct sockaddr *)&ad, &size);
    if (fd == -1)
    {
        std::cerr << "accept failed"<< std::endl; 
        return ;
    }
    this->fds.push_back((struct pollfd){fd, POLLIN, 0});
    int clientPort = ntohs(ad.sin_port);
    std::string clientHost(inet_ntoa(ad.sin_addr));
    // Client *client = new Client();
    // this->addClient(client);
}

