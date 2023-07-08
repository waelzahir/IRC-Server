#include "Commands.hpp"

/*** ------------------------------- CONSTRUCTOR --------------------------------*/
Commands::Commands()
{
	std::cout << "Commands Constructor called" << std::endl;
}

Commands::Commands(const Commands &other)
{
	*this = other;
}

/*** -------------------------------- DESTRUCTOR --------------------------------*/
Commands::~Commands()
{
	std::cout << "Commands Destructor called" << std::endl;
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
    if (funcname == "CAP")
        return &Commands::cap;
    return NULL;
}

void	Commands::cap(Client *client, std::stringstream &stream)
{
	std::string req;
	std::getline(stream, req, ' ');
	if (req == "END")
		return ;
	std::string res(":ircserv CAP * LS :\r\n");
	send(client->fd, res.c_str(), res.length(), 0);

}

/*** --------------------------------- ACCESSOR ---------------------------------*/

/*** --------------------------------- ACEPTION ---------------------------------*/

