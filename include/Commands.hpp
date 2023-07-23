#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>
# include <string>
# include <set>
# include <vector>
# include <queue>
# include <algorithm>
# include <math.h>
# include <sstream>
# include "Client.hpp"
# include <sys/socket.h>
# include "macros.h"
class Server;
# include "Server.hpp"
// class Server;

class Commands
{
private:
public:
	Server *_server;
	Commands();
	Commands(Server *name);
	Commands(Commands const &);
	~Commands();
	void	execute(Client *client, std::string Command);
	void    (Commands::*getCommand(std::string funcname)) (Client*,std::stringstream&);
	void	cap(Client *client, std::stringstream &stream);
	void	pass(Client *client, std::stringstream &stream);
	void	nick(Client *client, std::stringstream &stream);
	void	user(Client *client, std::stringstream &stream);
	void	mode(Client *client, std::stringstream &stream);
	void	join(Client *client, std::stringstream &stream);
	void	who(Client *client, std::stringstream &stream);
	void	privmsg(Client *client, std::stringstream &stream);
	void	quit(Client *client, std::stringstream &stream);
	void	welcome(Client *client, std::stringstream &stream);
	void	bot(Client *client, std::stringstream &stream);

	
	// helpers
	void check_channel(std::string &channel);

	Commands&	operator=(Commands const &);
};

#endif /* * SPAN_H */
