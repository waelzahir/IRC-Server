/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:25:36 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/22 12:19:15 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* public methods */

Server::~Server()
{
    while (this->clients.size())
    {
        close((this->clients.begin())->second->fd);
        delete ((this->clients.begin()->second));
        this->clients.erase(this->clients.begin());
    }
}

Server::Server(std::string pass, int port, int serial )
{
    std::stringstream serialto_str;
    std::string serial_str;
    
    serialto_str << serial;
    serialto_str >> serial_str;
     
    std::cout << "constructor " << pass << " on port "<< port << std::endl;
    if (pass.length() < 2)  
        throw "can't accept this password";
    this->password = pass;
    this->port = port;
    this->serverName = ":Ircsrvr" + serial_str + ".local";
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
    this->execReq();
}


void    Server::disconect()
{
    /* deleting channels and */
    close(this->listensocket);
}



int    Server::createChannel(Channel& channel)
{
    std::map<std::string, Channel>::iterator it;
	it = channels.find(channel._name);
	if (it != channels.end())
    {
        std::cerr << "create channel: channel exist" << std::endl; 
        return 1;
    }
    this->channels.insert(std::make_pair(channel._name,  channel));
    return 0;
}



int    Server::removeChannel(Channel &channel)
{
    std::map<std::string, Channel>::iterator it;
	it = channels.find(channel._name);
	if (it != channels.end())
		return channels.erase(it), 0;
    return 1;
}


void    Server::addClient(Client *client)
{
    this->clients.insert(std::make_pair(client->fd, client));
}





void    Server::removeClient(Client *client)
{

    std::map<std::string, Channel>::iterator it;
    if (client == NULL)
        {
            /*handle error acordinly*/
            return ;
        }
    try
    {
        this->clients.at(client->fd);
    }
    catch (...)
    {
        return ;
    }
    Message mess(*client, "PART", client->_client_user.nickname);
    for (it = channels.begin(); it != channels.end(); it++)
    {
        if ((*it).second.remove_user(client->_client_user))
            continue;
        mess.add_param((*it).second._name);
        sendMessageChannel(mess,(*it).second._name);
        mess.clear_final();
    }
    
    this->clients.erase(client->fd);
    if (client->_client_user.nickname.length())
        this->nickmak.erase(client->_client_user.nickname);
    std::cout << "client disconected" << std::endl;
}





void    Server::sendMessage(Message message) /* this method broadcast message to  client*/
{
    message.set_message();
    send(message._sender.fd, message._final_message.c_str(), message.size(),0);
}

void    Server::sendMessage_err(Message message) /* this method broadcast message to  client*/
{
    send(message._sender.fd, message._final_message.c_str(), message.size(),0);
}

void    Server::sendMessage(Message& message, const Client &cl) /* this method broadcast message to  client*/
{
    message.set_message();
    std::cout << cl._client_user.nickname << std::endl; 
    std::cout << message._final_message << std::endl; 
    send(cl.fd, message._final_message.c_str(), message.size(),0);
}
void    Server::sendMessage_user(Message& message, std::string &nickname, const Channel& channel) /* this method broadcast message to  client*/
{
    try
    {
        Client *cl =  nickmak.at(nickname);
        send((*cl).fd, message._final_message.c_str(), message.size(),0);
    }
    catch(const std::exception& e)
    { 
        
        // check user not found in nickmak
        const_cast<Channel &>(channel).remove_user(User("", nickname));    
    }
}

void    Server::sendMessageALL(Message& message) /* this method broadcast message to every client*/
{
    std::map<int, Client *>::iterator it;

    message.set_message();
    for (it  = clients.begin(); it != clients.end(); it++)
    {
        std::cout << (*it).second->_client_user.nickname << std::endl; 
        std::cout << message._final_message << std::endl; 
        send((*it).second->fd, message._final_message.c_str(), message.size(),0);
    }
}
void    Server::sendMessageChannel(Message& message, std::string channel)
{
    std::vector<User>::iterator it;

    try
    {
        std::vector<User>&users = channels.at(channel)._users;
        /* code */
        message.set_message();
        std::cout << message._final_message << std::endl;
        for (it  = users.begin(); it != users.end(); it++)
        {
            if ((*it).nickname != message._sender._client_user.nickname)
                sendMessage_user(message,(*it).nickname, channels.at(channel));
        }
    }
    catch(const std::exception& e)
    {
        message.set_message_error(ERR_NOSUCHNICK(this->serverName, message._sender._client_user.nickname, channel));
        this->sendMessage_err(message);
        // channel not found
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
    if (fds[0].revents & 1 )
    {
        this->acceptNewClient();
        poll_num--;
    }
    for (size_t i = 0; i < fds.size() && poll_num; i++)
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
    Client *client = new Client();
    client->host =  inet_ntoa(ad.sin_addr);
    client->port =  ntohs(ad.sin_port);
    client->fd = fd;
    this->addClient(client);
}

int    Server::get_message(int fd, int index)
{
    char    buffer[1024];
    bzero(buffer, 1024);
    Client *client = this->get_client_adress(fd);
    int res = recv(fd, buffer, 1000, 0);
    if (res == 0)
    {
        this->removeClient(client);
        this->fds.erase(this->fds.begin() + index);
        index--;
        return -1;
    
    }
    client->messages += buffer;
    this->pushToQueue(fd);
    return 0;
}
Client* Server::get_client_adress(int fd)
{
    Client* client;
    try
    {
        client  = this->clients.at(fd);
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
    Client *client = this->get_client_adress(fd);
    while (1)
    {
        pos = client->messages.find("\r\n",0);
        if (pos == std::string::npos)
            break ;
        std::string full = client->messages.substr(0, pos);
        this->Mqueue.push(make_pair(fd, full));
        client->messages.erase(0, pos+2);
    }
}

void    Server::execReq()
{
    if (!this->Mqueue.size())
        return ;
    while (this->Mqueue.size())
    {
        Commands command(this);
        command.execute(get_client_adress(this->Mqueue.front().first) ,this->Mqueue.front().second);
        this->Mqueue.pop();
    }

}

bool    Server::checkNick(std::string &nick, Client *client)
{
    Client *cl;
    try
    {
        cl = nickmak.at(nick);
        if (cl == client)
        {
            nickmak.erase(nick);
            std::string message;
            message = ":" +  client->_client_user.nickname + "!~" + client->_client_user.username + "@"+ client->host + " NICK :" + nick + "\r\n"; 
            send(client->fd, message.c_str(), message.length(), 0);
            return false;
        }
    }
    catch (...)
    {
        if (client->_client_user.nickname.length())
        {
            std::string message;
            message = ":" +  client->_client_user.nickname + "!~" + client->_client_user.username + "@"+ client->host + " NICK :" + nick + "\r\n"; 
            send(client->fd, message.c_str(), message.length(), 0);
        }
        return false;
    }
    return true;
}

