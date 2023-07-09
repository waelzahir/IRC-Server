#include "Commands.hpp"
#include "ReqParser.hpp"
#include "Server.hpp"

void	Commands::user(Client *client, std::stringstream &stream)
{
	ReqParser	parser(stream);
	std::string message;
	if (client->_client_user.username.size())
	{
		message = ERR_ALREADYREGISTERED(this->server->serverName, client->_client_user.nickname, "USER");
		send(client->fd, message.c_str(), message.length() , 0);
		return ;
	}
	if (!parser.getStatus())
	{
		message = ERR_NEEDMOREPARAMS(this->server->serverName, "*", "USER");
		send(client->fd, message.c_str(), message.length() , 0);
		return ;
	}
	std::pair<int, std::string> tpair = parser.getToken();
	client->_client_user.username = tpair.second;
	client->_client_user.activateAuth();

}