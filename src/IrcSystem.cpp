#include "IrcSystem.hpp"

/*** ------------------------------- CONSTRUCTOR --------------------------------*/
IrcSystem::IrcSystem()
{
	std::cout << "IrcSystem Constructor called" << std::endl;
}

IrcSystem::IrcSystem(const IrcSystem &other)
{
	*this = other;
}

/*** -------------------------------- DESTRUCTOR --------------------------------*/
IrcSystem::~IrcSystem()
{
	// delete server;
	std::cout << "IrcSystem Destructor called" << std::endl;
}

/*** --------------------------------- OVERLOAD ---------------------------------*/
IrcSystem&   IrcSystem::operator=(IrcSystem const & other )
{
	(void)other;
	return *this;
}

/*** --------------------------------- METHODS ----------------------------------*/
void IrcSystem::start_loop()
{
	while (true)
	{
		try
		{
			server->connect();
		}
		catch(const std::exception& e)
		{
			std::cerr << "server not connected" << '\n';
			sleep(2);
			start_loop();
		}
	}
}


void IrcSystem::set_server(Server _server)
{
	this->server = new Server(_server);
}



void IrcSystem::remove_server()
{
	// delete server;
}
void IrcSystem::addUser(const User& _user)
{
	users.push_back(_user);
}

void IrcSystem::removeUser(std::string username)
{
	std::vector<User>::iterator it;
	it = find(users.begin(), users.end(), User(username, "bullshit"));
	if (it != users.end())
		users.erase(it);
}
/*** --------------------------------- ACCESSOR ---------------------------------*/

/*** --------------------------------- ACEPTION ---------------------------------*/

