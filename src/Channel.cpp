#include "Channel.hpp"

/*** ------------------------------- CONSTRUCTOR --------------------------------*/
Channel::Channel()
{
	std::cout << "Channel Constructor called" << std::endl;
}
Channel::Channel(std::string name) : _name(name) , mode(0)
{
	
}

Channel::Channel(const Channel &other)
{
	*this = other;
}

/*** -------------------------------- DESTRUCTOR --------------------------------*/
Channel::~Channel()
{
	std::cout << "Channel Destructor called" << std::endl;
}

/*** --------------------------------- OVERLOAD ---------------------------------*/
Channel&   Channel::operator=(Channel const & other )
{
	(void)other;
	return *this;
}

/*** --------------------------------- METHODS ----------------------------------*/

void Channel::add_user(User &user)
{
	std::vector<User>::iterator it;
	it = find(_users.begin(), _users.end(), user);
	if (it == _users.end())
		_users.push_back(user);
}
void Channel::remove_user(User &user)
{
	std::vector<User>::iterator it;
	it = find(_users.begin(), _users.end(), user);
	if (it != _users.end())
		_users.erase(it);
}

void Channel::set_mode(int flag)
{
	mode |= flag;
}
void Channel::unset_mode(int flag)
{
	mode &= ~flag;

}
bool Channel::get_mode_status(int flag)
{
	return (mode & flag);
}
/*** --------------------------------- ACCESSOR ---------------------------------*/

/*** --------------------------------- ACEPTION ---------------------------------*/

