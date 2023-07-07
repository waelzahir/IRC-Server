#include "Client.hpp"

/*** ------------------------------- CONSTRUCTOR --------------------------------*/
Client::Client() : fd(-1)
{
}

Client::Client(const Client &other)
{
	*this = other;
}

/*** -------------------------------- DESTRUCTOR --------------------------------*/
Client::~Client()
{
}

/*** --------------------------------- OVERLOAD ---------------------------------*/
Client&   Client::operator=(Client const & other )
{
	this->fd = other.fd;
	this->_client_user = other._client_user;
	return *this;
}


/*** --------------------------------- METHODS ----------------------------------*/


void Client::set_client_user(User &user)
{
	_client_user = user;
}
void Client::join_channel(Channel& channel)
{
	std::vector<User>::iterator it;
	it = find(channel._users.begin(), channel._users.end(), _client_user);
	if (it == channel._users.end())
		channel._users.push_back(_client_user);
}

void Client::leave_channel(Channel& channel)
{
	std::vector<User>::iterator it;
	it = find(channel._users.begin(), channel._users.end(), _client_user);
	if (it != channel._users.end())
		channel._users.erase(it);
}

/*** --------------------------------- ACCESSOR ---------------------------------*/

/*** --------------------------------- ACEPTION ---------------------------------*/

