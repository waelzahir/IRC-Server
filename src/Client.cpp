#include "Client.hpp"

/*** ------------------------------- CONSTRUCTOR --------------------------------*/
Client::Client() : fd(-1)
{
	std::cout << "Client Constructor called" << std::endl;
}

Client::Client(const Client &other)
{
	*this = other;
}

/*** -------------------------------- DESTRUCTOR --------------------------------*/
Client::~Client()
{
	std::cout << "Client Destructor called" << std::endl;
}

/*** --------------------------------- OVERLOAD ---------------------------------*/
Client&   Client::operator=(Client const & other )
{
	(void)other;
	return *this;
}


/*** --------------------------------- METHODS ----------------------------------*/
void Client::join_channel(Channel& channel)
{
	std::vector<User>::iterator it;
	it = find(channel._users.begin(), channel._users.end(), _client_user.nickname);
	if (it == channel._users.end())
		channel._users.push_back(User(_client_user.username, _client_user.nickname));
}

void Client::leave_channel(Channel& channel)
{
	std::vector<User>::iterator it;
	it = find(channel._users.begin(), channel._users.end(), _client_user.nickname);
	if (it != channel._users.end())
		channel._users.erase(it);
}

/*** --------------------------------- ACCESSOR ---------------------------------*/

/*** --------------------------------- ACEPTION ---------------------------------*/

