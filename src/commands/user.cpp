#include "Commands.hpp"
#include "ReqParser.hpp"
#include "Server.hpp"


void	Commands::user(Client *client, std::stringstream &stream)
{
	Message	err(*client, "USER");
	std::string user;
	std::string filler;
	int i = 0;
	stream >> user;
	std::string message;

	while (!stream.eof())
	{
		stream >> filler;
		std::cout << i << " " << filler<<std::endl;
		i++;
	}
	if (i < 3)
	{
		err.set_message_error(ERR_NEEDMOREPARAMS(this->_server->serverName, "*", "USER"));
		_server->sendMessage_err(err);
		return ;
	}
	if (client->_client_user.username.size())
	{
		err.set_message_error(ERR_ALREADYREGISTERED(this->_server->serverName, client->_client_user.nickname, "USER"));
		_server->sendMessage_err(err);
		return ;
	}
	client->_client_user.username = user;
	client->_client_user.activateAuth();
}