/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:43:51 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/23 23:34:34 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Server.hpp"
#include "ReqParser.hpp"

static bool isChannel(std::string name)
{
    char c = name[0];
    return (c == '#');
}
static void sendHelper(std::string message, int destination)
{
    send(destination, message.c_str(), message.length(), 0);
}
static void sendHelper(std::string message, Channel &chanel)
{
}


void Commands::privmsg(Client *client, std::stringstream &stream)
{
    ReqParser parser(stream);
    Message message(*client, "PRIVMSG", client->_client_user.nickname);

    if (parser.getStatus() < 2)
    {
        (parser.getStatus() == 0) ? sendHelper(ERR_NORECIPIENT(this->_server->serverName, client->_client_user.nickname, "PRIVMSG"), client->fd) : sendHelper(ERR_NOTEXTTOSEND(this->_server->serverName, client->_client_user.nickname), client->fd);
        return;
    }
    std::pair<int, std::string> where = parser.getToken();
    std::pair<int, std::string> what = parser.getToken();
    if (where.first != 1)
    {
        try
        {
            if (isChannel(where.second))
            {
                Channel& channel= this->_server->channels.at(where.second);
                if (!channel.get_user(client->_client_user))
                {
                    sendHelper(ERR_CANNOTSENDTOCHAN(this->_server->serverName, client->_client_user.nickname, where.second), client->fd);
                    return;
                }    
                message.set_param(where.second);
                message.set_trailing(what.second);
                _server->sendMessageChannel(message, where.second);
                message.clear_final();
            }
            else
            {
                Message message(*client, "PRIVMSG", client->_client_user.nickname);
                message.set_param(where.second);
                message.set_trailing(what.second);
                _server->sendMessage(message, *this->_server->nickmak.at(where.second));
                message.clear_final();
            }
            return;
        }
        catch (...)
        {
            sendHelper(ERR_NOSUCHNICK(this->_server->serverName, client->_client_user.nickname, where.second), client->fd);
            return;
        }
    }
    int loop = parser.ListedParse(where);
    while (loop)
    {
        where = parser.getToken();
        try
        {
            if (isChannel(where.second))
            {
              
                Channel& channel = this->_server->channels.at(where.second);
                if (!channel.get_user(client->_client_user))
                {
                    sendHelper(ERR_CANNOTSENDTOCHAN(this->_server->serverName, client->_client_user.nickname, where.second), client->fd);
                    loop--;
                    continue;
                }
                
                message.set_param(where.second);
                message.set_trailing(what.second);
                _server->sendMessageChannel(message, where.second);
                message.clear_final();
                /* do something*/
            }
            else
            {
                message.set_param(where.second);
                message.set_trailing(what.second);
                _server->sendMessage(message, *this->_server->nickmak.at(where.second));
                message.clear_final();
            }
        }
        catch (...)
        {
            sendHelper(ERR_NOSUCHNICK(this->_server->serverName, client->_client_user.nickname, where.second), client->fd);
        }
        loop--;
    }
}