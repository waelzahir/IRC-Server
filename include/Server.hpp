/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:25:49 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/04 19:42:31 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <vector>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <queue>
#include <map>
#include <sys/socket.h>
#include <strings.h>
#include <cstdlib>
#include <stack>
#include <stdio.h>
#include  <cstring>
#include <sstream>

#include "Client.hpp"
#include "Channel.hpp"
#include "Message.hpp"
class Server
{
    public:
        Server(std::string pass, int port, int serial = 0);
        ~Server();
        void    connect();
        void    disconect();
        void    createChannel(Channel *channel);
        void    removeChannel(Channel *channel);
        void    addClient(Client *client);
        void    removeClient(Client *client);
        void    sendMessage(Message message); /* this method broadcast message to every client*/
        
        std::string serverName; /*wht not server name ??*/
        int         port;
        std::vector<Channel *> channels;
        std::vector<Client  *> clients;
    private:
        int listensocket;
        std::string password;
        std::vector<struct pollfd> fds;
        std::map<int , Client *>   fdmapping;
        std::map<int , std::string> messagemap; /*this map have full and the fragmented request than need to be full to be pushed to the message requests*/
        std::queue<std::pair<int, std::string> > Mqueue; /* this queue contains the only full request containing (\r\n)*/

        void    createSocket();
        void    makeNonBlockSocket();
        void    makePortReusable();
        void    goBindSocket();
        void    getEvent(int poll_num);
        void    acceptNewClient();
        int     get_message(int fd,int index);
        Client *get_client_adress(int fd);
        void    pushToQueue(int fd);

};
#endif