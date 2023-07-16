#include "Channel.hpp"

/*** ------------------------------- CONSTRUCTOR --------------------------------*/
Channel::Channel()
{
	std::cout << "Channel Constructor called" << std::endl;
}
Channel::Channel(std::string name) : _name(name) , mode(0), _key("")
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
	this->_name  = other._name;
	this->_key   = other._key;
	this->_users = other._users;
	this->_owner = other._owner;
	return *this;
}
bool Channel::operator == (const Channel &_o)
{
	if (_o._name == this->_name)
		return true;
	return false;
}
bool Channel::operator == (Channel &_o)
{
	if (_o._name == this->_name)
		return true;
	return false;
}


/*** --------------------------------- METHODS ----------------------------------*/

int Channel::add_user(User &user, std::string &key)
{
	std::vector<User>::iterator it;
	it = find(_users.begin(), _users.end(), user);
	if (it == _users.end())
	{
		if (_key == key)
			_users.push_back(user);
		else 
			return 1;
	}
	else
		return 2;
	return 0;
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

