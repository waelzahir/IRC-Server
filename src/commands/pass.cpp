
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
		message = ERR_ALREADYREGISTERED(this->_server->serverName, client->_client_user.nickname, "PASS");
		send(client->fd, message.c_str(), message.length() , 0);
		return ;
	}
	std::string token = nextToken(stream);
	if (!token.length())
	{
		message = ERR_NEEDMOREPARAMS(this->_server->serverName, "*", "PASS");
		send(client->fd, message.c_str(), message.length() , 0);
		return ;
	}
	if (token == this->_server->password)
	{
		client->_client_user.pass_auth = token;
		client->_client_user.activateAuth();
		return ; 
	}
	message = ERR_PASSWDMISMATCH(this->_server->serverName, "*");
	send(client->fd, message.c_str(), message.length() , 0);

}