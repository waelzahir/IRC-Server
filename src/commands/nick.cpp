/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:30:43 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/27 02:56:56 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Commands.hpp"
#include "Server.hpp"



static bool otherCharExeptions(char	c)
{
	return (c == '{' || c == '}' || c == '[' || c == ']' || c == '|' || c == '_');	
}
static	bool checkNickValidity(std::string &nick)
{
	for (std::size_t i = 0; i < nick.length(); i++)
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