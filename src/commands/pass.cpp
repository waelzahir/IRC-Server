/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:52:47 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/26 20:02:35 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Commands.hpp"
#include "Server.hpp"

void	Commands::pass(Client *client, std::stringstream &stream)
{
	Message err(*client, "PASS");
	std::string token;
	stream >> token;
	if (client->_client_user.pass_auth.size())
	{
		err.set_message_error(ERR_ALREADYREGISTERED(this->_server->serverName, client->_client_user.nickname, "PASS"));
		_server->sendMessage_err(err);
		return ;
	}
	if (!token.length())
	{
		err.set_message_error(ERR_NEEDMOREPARAMS(this->_server->serverName, "*", "PASS"));
		_server->sendMessage_err(err);
		return ;
	}
	if (token == this->_server->password)
	{
		client->_client_user.pass_auth = token;
		client->_client_user.activateAuth();
		return ; 
	}
	err.set_message_error(ERR_PASSWDMISMATCH(this->_server->serverName, "*"));
	_server->sendMessage_err(err);
}