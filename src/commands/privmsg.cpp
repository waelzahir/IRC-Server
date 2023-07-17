/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:43:51 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/17 23:57:23 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Commands.hpp"
#include "Server.hpp"
#include "ReqParser.hpp"

static bool isChannel(std::string name)
{
    char prefix = name[0];
    return (c == '#')
}
static void sendHelper(std::string message, int destination)
{
    send(destination, message.c_str(), message.length(), 0);
}
static void sendHelper(std::string message, Channel &chanel)
{
    
}
void	Commands::privmsg(Client *client, std::stringstream &stream)
{
    ReqParser	parser(stream);
    std::string message;
    
    if (parser.getStatus() < 2)
	{
        (parser.getStatus() == 0) ? sendHelper(ERR_NORECIPIENT(this->_server->serverName, client->_client_user.nickname, "PRIVMSG"), client->fd) : sendHelper(ERR_NOTEXTTOSEND(this->_server->serverName, client->_client_user.nickname), client->fd);
		return ;
	}
    std::pair<int, std::string> where = parser.getToken();
    std::pair<int, std::string> what = parser.getToken();
    if (where.first != 1)
        try
        {
            if (ishannel(where.second))
            {
                /* do something*/ 
            }
            else
            {
                Client *cli = this->_server->nickmak.at(where.second);
                sendHelper(std::string(":") + cli->_client_user.nickname + "!~" + cli->_client_user.nickname + "@" + cli->host + " PRIVMSG " + where.second + " :" + what.second + "\r\n", cli->fd);
            }
            return ;
        }
        catch (...)
        {
            sendHelper(ERR_NOSUCHNICK(this->_server->serverName, client->_client_user.nickname, where.second), client->fd);
            return ;
        }
    int loop = parser.ListedParse(where);
    while (loop)
    {
        where = parser.getToken();
        try
        {
            if (ishannel(where.second))
            {
                /* do something*/   
            }
            else
            {
                Client *cli = this->_server->nickmak.at(where.second);
                sendHelper(std::string(":") + cli->_client_user.nickname + "!~" + cli->_client_user.nickname + "@" + cli->host + " PRIVMSG " + where.second + " :" + what.second + "\r\n", cli->fd);
            }
            return ;
        }
        catch (...)
        {
            sendHelper(ERR_NOSUCHNICK(this->_server->serverName, client->_client_user.nickname, where.second), client->fd);
            return ;
        }
        loop--;
    }
}

// sendHelper(ERR_NOSUCHNICK(this->_server->serverName, client->_client_user.nickname, destt.second),client->fd);
