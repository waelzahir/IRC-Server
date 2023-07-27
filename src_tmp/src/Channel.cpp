#include "Channel.hpp"

/*** ------------------------------- CONSTRUCTOR --------------------------------*/
Channel::Channel()
{

}
Channel::Channel(std::string name) : _name(name) , mode(0), _key("") , _topic("")
{
	_user_limit = -1;
	std::time_t currentTime = std::time(NULL);
    std::stringstream ss;
    ss << currentTime;
    _create_time = ss.str();
}

Channel::Channel(const Channel &other)
{
	*this = other;
}

/*** -------------------------------- DESTRUCTOR --------------------------------*/
Channel::~Channel()
{
}

/*** --------------------------------- OVERLOAD ---------------------------------*/
Channel&   Channel::operator=(Channel const & other )
{
	this->_name  = other._name;
	this->_key   = other._key;
	this->_users = other._users;
	this->_topic_time = other._topic_time;
	this->_topic = other._topic;
	this->_topic_seter = other._topic_seter;
	_user_limit = other._user_limit;
	_topic  = other._topic;
	inveted = other.inveted;
	mode = other.mode;
	_create_time = other._create_time;

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
int Channel::remove_user(User &user)
{
	std::vector<User>::iterator it;
	it = find(_users.begin(), _users.end(), user);
	if (it != _users.end())
		return _users.erase(it), 0;
	return 1;
}
int Channel::remove_user(const User &user)
{
	std::vector<User>::iterator it;
	it = find(_users.begin(), _users.end(), user);
	if (it != _users.end())
		return _users.erase(it), 0;
	return 1;
}



std::string Channel::get_channels_users()
{
	std::string lst;
	std::vector<User>::iterator it;

	for (it = _users.begin(); it != _users.end();it++ )
	{
		if ((*it).owner == 1)
			lst += "@";
		lst += (*it).nickname;
		if ((it + 1) != _users.end())
			lst += " ";
	}
	return lst;
}


User* Channel::get_user(std::string &nickname)
{
	std::vector<User>::iterator it = find(_users.begin(), _users.end(),User("", nickname));
	if (it != _users.end())
		return &(*it);
	return NULL;
}
User* Channel::get_user(const std::string &nickname)
{
	std::vector<User>::iterator it = find(_users.begin(), _users.end(),User("", nickname));
	if (it != _users.end())
		return &(*it);
	return NULL;
}

User* Channel::get_user(const User& user)
{
	std::vector<User>::iterator it = find(_users.begin(), _users.end(),user);
	if (it != _users.end())
		return &(*it);
	return NULL;
}
User* Channel::get_user(User& user)
{
	std::vector<User>::iterator it = find(_users.begin(), _users.end(),user);
	if (it != _users.end())
		return &(*it);
	return NULL;
}

bool  Channel::is_operator(User &user)
{
	User *_us = get_user(user);
	
	if (_us &&  _us->owner == 1)
		return true;
	return false;
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

