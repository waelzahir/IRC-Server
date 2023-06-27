/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pp <pp@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:25:36 by ozahir            #+#    #+#             */
/*   Updated: 2023/06/27 19:31:30 by pp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

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

Server::Server(std::string pass, int port, int serial )
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
    for (int i = 0; i < Mqueue.size(); i++)
    {
        std::cout << Mqueue.front().second << std::endl;
        Mqueue.pop();
        std::cout << i << " queue printed " << std::endl;
 
    }
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
   std::vector<Channel *>::iterator it = this->channels.begin();
   while (it != this->channels.end())
   {
        if (*it == channel)
            break;
        it++;
   }
   if (it == this->channels.end())
        return ;
    delete channel;
    this->channels.erase(it);
}


void    Server::addClient(Client *client)
{
    this->clients.push_back(client);
}





void    Server::removeClient(Client *client)
{

    if (client == nullptr)
        {
            /*handle error acordinly*/
            return ;
        }
    std::vector<Client *>::iterator it = this->clients.begin();
    while (it != this->clients.end())
    {
        std::cout << this->clients.size()<< " " << client << " " << *it << std::endl;

        if (*it == client)
        {
            break ;
        }
  
        it++;
    }
    if (it == this->clients.end())
        return ;
    delete client;
    this->clients.erase(it);
    std::cout << "client disconected" << std::endl;
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
    {
        this->acceptNewClient();
        poll_num--;
    }
    for (size_t i = 0; i < fds.size(); i++)
    {
        if (fds[i].revents & 1)
        {
            if (this->get_message(fds[i].fd, i) == -1)
                i--;
            poll_num--;
        }
    }
    
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
    Client *client = new Client();
    this->addClient(client);
    std::cout << port << " " << clientHost << std::endl;
    this->fdmapping.insert(std::make_pair(fd, client));
    messagemap.insert(std::make_pair(fd, ""));
}

int    Server::get_message(int fd, int index)
{
    char    buffer[1024];
    bzero(buffer, 1024);
    int res = recv(fd, buffer, 1000, 0);
    if (res == 0)
    {
        this->removeClient( this->get_client_adress(fd));
        fdmapping.erase(fd);
        this->fds.erase(this->fds.begin() + index);
        index--;
        return -1;
    
    }
    messagemap[fd] += buffer;
    this->pushToQueue(fd);
    return 0;
}
Client* Server::get_client_adress(int fd)
{
    Client* client;
    try
    {
        client   =fdmapping.at(fd);
    }
    catch (...)
    {
        return NULL;
    }
    return client;
}
void    Server::pushToQueue(int fd)
{
    size_t pos;
    pos = messagemap[fd].find("\r\n",0);
    if (pos == std::string::npos)
        return ;
    std::string full = messagemap[fd].substr(0, pos+2);
    this->Mqueue.push(make_pair(fd, full));
    messagemap[fd].erase(0, pos+2);
}
