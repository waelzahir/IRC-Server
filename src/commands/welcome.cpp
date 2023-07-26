/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:55:44 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/26 20:29:41 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Commands.hpp"
#include "Server.hpp"


std::string to_string(int nb)
{
    std::stringstream  stream;
    stream << nb;
    return stream.str();
}

void	Commands::welcome(Client *client, std::stringstream &stream)
{
    std::string message;
    message = RPL_WELCOME(this->_server->serverName, client->_client_user.nickname);
    send(client->fd, message.c_str(), message.length(), 0);
    message =  RPL_YOURHOST(this->_server->serverName , to_string(this->_server->port), client->_client_user.nickname);
    send(client->fd, message.c_str(), message.length(), 0);
    message = RPL_CREATED(this->_server->serverName, client->_client_user.nickname, "32", "janvi", "2023");
    send(client->fd, message.c_str(), message.length(), 0);
    message = RPL_MYINFO(this->_server->serverName, client->_client_user.nickname , "taha");
    send(client->fd, message.c_str(), message.length(), 0);
    message = RPL_ISUPPORT(this->_server->serverName, client->_client_user.nickname );
    send(client->fd, message.c_str(), message.length(), 0);
}
