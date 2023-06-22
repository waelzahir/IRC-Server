/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:25:49 by ozahir            #+#    #+#             */
/*   Updated: 2023/06/22 23:05:56 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

class Server
{
    public:
        Server(std::string &pass, int port);
        void    connect();
        void    disconect();
        void    createChannel(Channel *channel);
        void    removeChannel(Channel *channel);
        void    addClient(Client *client);
        void    removeClient(Client *client);
        void    sendMessage(std::string &message); /* this method broadcast message to every client*/
        
        std::string ip; /*wht not server name ??*/
        int         port;
        std::vector<Channel *> channels;
        std::vector<Client  *> clients;
    private:
        void    createSocket();
        void    makeNonBlockSocket();
        void    makePortReusable();
        void    goBindSocket();

        int listensocket;
        std::string password;
};
#endif