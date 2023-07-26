/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:30:43 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/26 19:06:42 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Commands.hpp"
#include "Server.hpp"
#include "ReqParser.hpp"


static	std::string nextToken(std::stringstream &stream)
{
	std::string token;
	while (std::getline(stream, token, ' '))
		if (token.length())
			break ;
	return token;
} 
static bool otherCharExeptions(char	c)
{
	return (c == '{' || c == '}' || c == '[' || c == ']' || c == '|');	
}
static	bool checkNickValidity(std::string &nick)
{
	for (int i = 0; i < nick.length(); i++)
	{
		if (!isalpha(nick[i]) && !isdigit(nick[i]) && !otherCharExeptions(nick[i]))
			return 1;
	}
	if (isdigit(nick[0]))
		return 1;
	return 0;
}
void	Commands::nick(Client *client, std::stringstream &stream)
{
	std::string nick;
	Message err(*client, "NICK");
	stream >> nick;
	
	if (!nick.length())
	{
		err.set_message_error(ERR_NONICKNAMEGIVEN(this->_server->serverName, "*"));
		_server->sendMessage_err(err);
		return ;
	}
	if (checkNickValidity(nick))
	{
		err.set_message_error(ERR_ERRONEUSNICKNAME(this->_server->serverName, "*", nick));
		_server->sendMessage_err(err);
		return ;
	}
	if (this->_server->checkNick(nick, client))
	{
		err.set_message_error(ERR_NICKNAMEINUSE(this->_server->serverName, "*", nick));
		_server->sendMessage_err(err);
		return ;
	}
	this->_server->nickmak.insert(std::make_pair(nick, client));
	client->_client_user.nickname = nick;
	client->_client_user.activateAuth();
}