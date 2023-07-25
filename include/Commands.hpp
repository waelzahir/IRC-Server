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
	Message *msg_tmp;
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
	void	kick(Client *client, std::stringstream &stream);
	void	privmsg(Client *client, std::stringstream &stream);
	void	notice(Client *client, std::stringstream &stream);
	void	quit(Client *client, std::stringstream &stream);
	void	welcome(Client *client, std::stringstream &stream);
	void	ping(Client *client, std::stringstream &stream);

	void	bot(Client *client, std::stringstream &stream);

	
	// helpers
	Channel& check_channel(std::string &channel);
	void get_option_and_args(Channel&,User &user, std::pair<std::string, std::string> & );
	std::string mode_i(Channel&,User &, const std::string &str, char sign);
	std::string mode__t(Channel&,User &, const std::string &str, char sign);
	std::string mode_k(Channel&,User &, const std::string &str, char sign);
	std::string mode_o(Channel&,User &, const std::string &str, char sign);
	std::string mode_l(Channel&,User &, const std::string &str, char sign);

	Commands&	operator=(Commands const &);
};

typedef std::string (Commands::*optr)(Channel&,User&,const std::string&, char);

#endif /* * SPAN_H */
