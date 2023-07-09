
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
void	Commands::pass(Client *client, std::stringstream &stream)
{
	std::string message;
	if (client->_client_user.pass_auth.size())
	{
		message = ERR_ALREADYREGISTERED(this->server->serverName, client->_client_user.nickname);
		send(client->fd, message.c_str(), message.length() , 0);
		return ;
	}
	std::string token = nextToken(stream);
	if (!token.length())
	{
		message = ERR_NEEDMOREPARAMS(this->server->serverName, std::string("*"), "PASS");
		send(client->fd, message.c_str(), message.length() , 0);
		return ;
	}
	if (token == this->server->password)
	{
		client->_client_user.pass_auth = token;
		return ; 
	}
	message = ERR_PASSWDMISMATCH(this->server->serverName, "*");
	send(client->fd, message.c_str(), message.length() , 0);
}