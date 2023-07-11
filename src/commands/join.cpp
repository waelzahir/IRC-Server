#include "Commands.hpp"

void	Commands::join(Client *client, std::stringstream &_stream)
{
	std::cout << "--------join start-------" << std::endl;
	std::string param;
	
	_stream >> param; 

	std::cout << param << std::endl;
	send(client->fd, ":Taha JOIN #test\n", sizeof(":Taha JOIN #test"), 0);
	std::cout << "--------join end-------" << std::endl;
}