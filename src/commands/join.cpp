#include "Commands.hpp"

void	Commands::join(Client *client, std::stringstream &_stream)
{
	std::cout << "--------join start-------" << std::endl;
	std::string param;
	
	_stream >> param; 
	std::cout << "--------join end-------" << std::endl;
}