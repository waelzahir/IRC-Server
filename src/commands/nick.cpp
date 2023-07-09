#include "Commands.hpp"
#include "Server.hpp"

static	std::string nextToken(std::stringstream &stream)
{
	std::string token;
	while (std::getline(stream, token, ' '))
		if (token.length())
			break ;
	return token;
} 
static	bool checkNickValidity(std::string &nick)
{
	if (nick[0] == ':' || nick[0] == '#' || nick[0] == '&' || isdigit(nick[0]) || !isalpha(nick[0]))
		return 1;
	return 0;
}
void	Commands::nick(Client *client, std::stringstream &stream)
{
	std::string token = nextToken(stream);
	std::string message;
	if (!token.length())
	{
		message = ERR_NONICKNAMEGIVEN(this->server->serverName, "*");
		send(client->fd, message.c_str(), message.length() , 0);
			return ;
	}
	if (checkNickValidity(token))
	{
		message = ERR_ERRONEUSNICKNAME(this->server->serverName, "*", token);
		send(client->fd, message.c_str(), message.length() , 0);
		return ;
	}
	if (this->server->checkNick(token, client))
	{
		message = ERR_NICKNAMEINUSE(this->server->serverName, "*", token);
		send(client->fd, message.c_str(), message.length() , 0);
		return ;
	}
	this->server->nickmak.insert(std::make_pair(token, client));
	client->_client_user.nickname = token;
	client->_client_user.activateAuth();
}