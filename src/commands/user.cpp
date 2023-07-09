#include "Commands.hpp"

void	Commands::user(Client *client, std::stringstream &stream)
{
	std::string token;
	while (std::getline(stream, token, ' '))
		if (token.length())
			break ;
	
}