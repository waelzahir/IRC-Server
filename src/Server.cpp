/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:25:36 by ozahir            #+#    #+#             */
/*   Updated: 2023/06/22 23:16:33 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* public methods */

Server::Server(std::string &pass, int port)
{
    if (pass.length() < 2)  
        throw "can't accept this password";
    this->password = pass;
    this->port = port;
    /* ?????????????*/
    this->ip = "127.0.0.1";
}

void    Server::connect()
{
    this->createSocket();
    this->makeNonBlockSocket();
    this->makePortReusable();
    this->goBindSocket();
    if (listen(this->listensocket, 5) == -1)
    {
        close(this->listensocket);
        throw "listen error";
    }
}


void    Server::disconect()
{
    while (clients.size())
    {
        close(clients[0].socket);
        delete clients[0];
        clients.erase(clients.begin());
    }
    while (channels.size())
    {
        delete channels[0];
        channels.erase(channels.begin());
    }
    close(this->listensocket);
}



void    Server::createChannel(Channel *channel)
{
    this->channels.push_back(channel);
}



void    removeChannel(Channel *channel)
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





void    Server::sendMessage(std::string &message); /* this method broadcast message to every client*/
{
    for (size_t i = 0; i < clients.size(); i++)
    {
        send(clients[i].socket, message.c_str(), message.length(), 0);
    }
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
        throw "setsock opt error";
    }
}
void    Server::goBindSocket()
{
    struct  sockaddr_in ad;
    bzero(&ad, sizeof (ad));
    ad.sin_family = AF_INET;
    ad.sin_addr.s_addr = inet_addr("0.0.0.0");
    ad.sin_port = htons(this->port);
    if (bind(fd, (struct sockaddr *)&ad, sizeof(ad))==-1)
    {
        close(fd);
        throw "bind error";
    }
}
