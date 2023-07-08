#include "Commands.hpp"

/*** ------------------------------- CONSTRUCTOR --------------------------------*/
Commands::Commands() 
{
	// std::cout << "Commands Constructor called" << std::endl;
}
Commands::Commands(Server *_server) : server(_server)
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
	return *this;
}

/*** --------------------------------- METHODS ----------------------------------*/
void	Commands::execute(Client *client, std::string Command)
{
	std::stringstream strm(Command);
	std::string name;
	std::cout <<  strm.str() << std::endl;
	if (!std::getline(strm, name, ' '))
		return ;
	void  (Commands::*ptr)(Client*, std::stringstream&) = this->getCommand(name);
	if (ptr == NULL)
		return ;
	(this->*ptr)(client, strm);
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

