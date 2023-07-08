#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>
# include <string>
# include <set>
# include <vector>
# include <algorithm>
# include <math.h>
# include <sstream>

class Client;
class Commands
{
public:
	Commands();
	Commands(Commands const &);
	~Commands();
	void	execute(Client *client, std::string Command);
	void    (Commands::*getCommand(std::string funcname)) (Client*,std::stringstream&);
	void	cap(Client *client, std::stringstream &stream);
	void pass(std::string, std::string _args);

	Commands&	operator=(Commands const &);
};

#endif /* * SPAN_H */