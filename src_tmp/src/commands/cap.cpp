#include "Commands.hpp"

void	Commands::cap(Client *client, std::stringstream &stream)
{
	std::string req;
	std::getline(stream, req, ' ');
	if (req == "END")
		return ;
	std::string res(":ircserv0.local CAP * LS :\r\n");
	send(client->fd, res.c_str(), res.length(), 0);
}
