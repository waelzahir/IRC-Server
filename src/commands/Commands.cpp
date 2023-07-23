#include "Commands.hpp"
#include "Server.hpp"
/*** ------------------------------- CONSTRUCTOR --------------------------------*/
Commands::Commands() 
{
	// std::cout << "Commands Constructor called" << std::endl;
}
Commands::Commands(Server *__server) : _server(__server)
{
	// std::cout << "Commands Constructor called" << std::endl;
}

Commands::Commands(const Commands &other)
{
	*this = other;
}

/*** -------------------------------- DESTRUCTOR --------------------------------*/
Commands::~Commands()
{
	// std::cout << "Commands Destructor called" << std::endl;
}

/*** --------------------------------- OVERLOAD ---------------------------------*/
Commands&   Commands::operator=(Commands const & other )
{
	this->_server =  other._server;
	return *this;
}

/*** --------------------------------- METHODS ----------------------------------*/
static bool authMethods(std::string name)
{
	return (name == "PASS" || name == "NICK" || name == "USER");
}
void	Commands::execute(Client *client, std::string Command)
{
	
	if (client == NULL)
		return ;
	std::stringstream strm(Command);
	std::string name;
	if (!std::getline(strm, name, ' '))
		return ;
	
	void  (Commands::*ptr)(Client*, std::stringstream&) = this->getCommand(name);
	if ((!authMethods(name) && !client->_client_user.connected ) || ptr == NULL)
	{
		std::string message;
		(client->_client_user.connected) ? message = ERR_UNKNOWNCOMMAND(this->_server->serverName, client->_client_user.nickname, name):
		message = ERR_NOTREGISTERED(this->_server->serverName, name);
		send(client->fd, message.c_str(), message.length(), 0);
		return ;
	}
	(this->*ptr)(client, strm);
	if (client->_client_user.connected && client->_client_user.welcomed)
	{
		client->_client_user.welcomed = 0;
		this->welcome(client, strm);
	}

}
void    (Commands::*Commands::getCommand(std::string funcname)) (Client*, std::stringstream&)
{
	typedef void (Commands::*cmptr)(Client*, std::stringstream&);

	std::map<std::string, cmptr> commands;

	commands["CAP"] = &Commands::cap;
	commands["USER"] = &Commands::user;
	commands["PASS"] = &Commands::pass;
	commands["NICK"] = &Commands::nick;
	commands["MODE"] = &Commands::mode;
	commands["JOIN"] = &Commands::join;
	commands["WHO"] = &Commands::who;
	commands["PRIVMSG"] = &Commands::privmsg;
	commands["QUIT"] = &Commands::quit;
	commands["BOT"] = &Commands::bot;



	try
	{
		return commands.at(funcname);
	}
	catch(const std::exception& e)
	{
    	return NULL;
	}
}


/*** --------------------------------- ACCESSOR ---------------------------------*/

/*** --------------------------------- ACEPTION ---------------------------------*/

