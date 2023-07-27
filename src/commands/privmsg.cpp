/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:43:51 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/27 02:39:53 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Server.hpp"

static std::stringstream &operator>>(std::stringstream &src, std::stringstream &dst)
{
	std::string temp;

	src >> temp;
	dst << temp;
	return dst;
}

static std::string extract_token(std::stringstream &src)
{
	std::string temp;

	if (src.eof())
		return std::string("");
	getline(src, temp, ',');
	return temp;
}

static bool isChannel(std::string name)
{
    if (!name.length())
        return false;
    return (name[0] == '#' || name[0] == '&');
}

void Commands::privmsg(Client *client, std::stringstream &stream)
{
    std::stringstream destinations;
    std::string msg;
    std::string all;
    stream >> destinations;
    while (!stream.eof())
    {
        stream >> msg;
        if (msg.length())
        all +=  msg + " " ;
    }
    if (all.length() && all[0] == ':')
        all.erase(0,1);
        
    if (!destinations.str().length())
    {
        Message err(*client, "PRIVMSG");
        err.set_message_error(ERR_NORECIPIENT(this->_server->serverName, client->_client_user.nickname, "PRIVMSG"));
        _server->sendMessage_err(err);
        return ;
    }
    if (!msg.length() || (msg.length()  == 1 && msg[0] == ':'))
    {
        Message err(*client, "PRIVMSG");
        err.set_message_error(ERR_NOTEXTTOSEND(this->_server->serverName, client->_client_user.nickname));
        _server->sendMessage_err(err);
        return ;
    }
    while (!destinations.eof())
    {
        Message message(*client, "PRIVMSG", client->_client_user.nickname + "!" + client->_client_user.username + "@" + client->host);
        std::string dest = extract_token(destinations);
        if (isChannel(dest))
        {
            try
            {
                Channel &chref = check_channel(dest);
                if (chref.get_user(client->_client_user) == NULL)
                    throw std::string("Client");
                message.set_param(dest);
                message.set_trailing(all);
                _server->sendMessageChannel(message, dest);
                message.clear_final();
            }
            catch(std::string& e)
            {
                if (e == "Client")
                {
                    Message err(*client, "PRIVMSG");
                    err.set_message_error(ERR_CANNOTSENDTOCHAN(this->_server->serverName, client->_client_user.nickname, dest));
                    _server->sendMessage_err(err);
                }
                else if (e == "ERR_NOSUCHCHANNEL")
                {
                    Message err(*client, "PRIVMSG");
                    err.set_message_error(ERR_NOSUCHNICK(this->_server->serverName, client->_client_user.nickname, dest));
                    _server->sendMessage_err(err);
                }
            }
        }
        else
        {
            message.set_param(dest);
            message.set_trailing(all);
            try
            {    
                _server->sendMessage(message, *this->_server->nickmak.at(dest));
                message.clear_final();
            }
            catch(...)
            {
                Message err(*client, "PRIVMSG");
                err.set_message_error(ERR_NOSUCHNICK(this->_server->serverName, client->_client_user.nickname, dest));
                _server->sendMessage_err(err);
                message.clear_final();
            }
        }
    }
}