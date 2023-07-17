/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:43:51 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/17 18:53:53 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Commands.hpp"
#include "Server.hpp"
#include "ReqParser.hpp"

void	Commands::privmsg(Client *client, std::stringstream &stream)
{
    ReqParser	parser(stream);
    std::string message;
    if (!parser.getStatus())
	{
        message = ERR_NORECIPIENT(this->_server->serverName, client->_client_user.nickname, "PRIVMSG");
		send(client->fd, message.c_str(), message.length() , 0);
		return ;
	}
    std::pair<int, std::string> destt = parser.getToken();
    if (!parser.getStatus())
	{
        message = ERR_NOTEXTTOSEND(this->_server->serverName, client->_client_user.nickname);
		send(client->fd, message.c_str(), message.length() , 0);
		return ;
	}
    std::pair<int, std::string> messaget = parser.getToken();
    int dest = 1;
    std::cout << destt.second << " " << messaget.second <<std::endl;
    if (destt.first == 1)
    {
        dest = parser.ListedParse(destt);
    }
    if (dest > 1)
    {
        while (dest)
        {
            destt = parser.getToken();
            if (isalpha(destt.second[0]))
            {
                try
                {
                    Client *cl = this->_server->nickmak.at(destt.second);
                    message = ":" + cl->_client_user.nickname + "!~"+  cl->_client_user.username + "@" + cl->host + " PRIVMSG " +  destt.second + " :" + messaget.second + "\r\n";
                    send(cl->fd, message.c_str(), message.length(), 0);

                }
                catch (...)
                {
                    message = ERR_NOSUCHNICK(this->_server->serverName, client->_client_user.nickname, destt.second);
                    send(client->fd, message.c_str(), message.length(), 0);
                }
            }
            dest--;
        }
    }
    else
    {
        if (isalpha(destt.second[0]))
            {
                try
                {
                    Client *cl = this->_server->nickmak.at(destt.second);
                    message = ":" + cl->_client_user.nickname + "!~"+  cl->_client_user.username + "@" + cl->host + " PRIVMSG " +  destt.second + " :" + messaget.second + "\r\n";
                    send(cl->fd, message.c_str(), message.length(), 0);

                }
                catch (...)
                {
                    message = ERR_NOSUCHNICK(this->_server->serverName, client->_client_user.nickname, destt.second);
                    send(client->fd, message.c_str(), message.length(), 0);
                }
            }
        
    }

}
