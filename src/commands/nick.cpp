/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:30:43 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/24 17:42:57 by ozahir           ###   ########.fr       */
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
		{
			std::cout << "hna" <<std::endl;
			return 1;
		}
	}
	if (isdigit(nick[0]))
		return 1;
	return 0;
}
void	Commands::nick(Client *client, std::stringstream &stream)
{
	std::string token = nextToken(stream);
	std::string message;
	if (!token.length())
	{
		message = ERR_NONICKNAMEGIVEN(this->_server->serverName, "*");
		send(client->fd, message.c_str(), message.length() , 0);
			return ;
	}
	if (checkNickValidity(token))
	{
		message = ERR_ERRONEUSNICKNAME(this->_server->serverName, "*", token);
		send(client->fd, message.c_str(), message.length() , 0);
		return ;
	}
	if (this->_server->checkNick(token, client))
	{
		message = ERR_NICKNAMEINUSE(this->_server->serverName, "*", token);
		send(client->fd, message.c_str(), message.length() , 0);
		return ;
	}
	this->_server->nickmak.insert(std::make_pair(token, client));
	client->_client_user.nickname = token;
	client->_client_user.activateAuth();
}