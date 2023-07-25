/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:55:51 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/25 20:58:27 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "Commands.hpp"
#include "Server.hpp"
#include "ReqParser.hpp"

static bool isChannel(std::string name)
{
    char c = name[0];
    return (c == '#' || c == '&');
}
static void sendHelper(std::string message, int destination)
{
    send(destination, message.c_str(), message.length(), 0);
}


void Commands::notice(Client *client, std::stringstream &stream)
{
    ReqParser parser(stream);
    Message message(*client, "NOTICE", client->_client_user.nickname + "!" + client->_client_user.username + "@" + client->host);

    if (parser.getStatus() < 2)
        return;
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
                    return;
                }    
                message.set_param(where.second);
                message.set_trailing(what.second);
                _server->sendMessageChannel(message, where.second);
                message.clear_final();
            }
            else
            {
                message.set_param(where.second);
                message.set_trailing(what.second);
                _server->sendMessage(message, *this->_server->nickmak.at(where.second));
                message.clear_final();
            }
            return;
        }
        catch (...)
        {
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
        }
        loop--;
    }
}