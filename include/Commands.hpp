#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>
# include <string>
# include <set>
# include <vector>
# include <algorithm>
# include <math.h>
# include <sstream>
# include "Client.hpp"
       #include <sys/socket.h>

class Commands
{
public:
	Commands();
	Commands(Commands const &);
	~Commands();
	void	execute(Client *client, std::string Command);
	void    (Commands::*getCommand(std::string funcname)) (Client*,std::stringstream&);
	void	cap(Client *client, std::stringstream &stream);
	void	pass(Client *client, std::stringstream &stream);
	void	nick(Client *client, std::stringstream &stream);
	void	user(Client *client, std::stringstream &stream);


	Commands&	operator=(Commands const &);
};

#endif /* * SPAN_H */
