#include "User.hpp"

/*** ------------------------------- CONSTRUCTOR --------------------------------*/
User::User(): connected(0)
{
	// std::cout << "User Constructor called" << std::endl;
}
User::User(std::string _u, std::string _n) : username(_u), nickname(_n)
{
	// std::cout << "User paramitrized Constructor called" << std::endl;
}

User::User(const User &other)
{
	*this = other;
}

/*** -------------------------------- DESTRUCTOR --------------------------------*/
User::~User()
{
	// std::cout << "User Destructor called : " << this->username << std::endl;
}

/*** --------------------------------- OVERLOAD ---------------------------------*/
User&   User::operator=(User const & other )
{
	this->nickname = other.nickname;
	this->username = other.username;
	return *this;
}
bool User::operator == (const User &_o)
{
	if (_o.nickname == this->nickname)
		return true;
	return false;
}
bool User::operator == (User &_o)
{
	if (_o.nickname == this->nickname)
		return true;
	return false;
}

/*** --------------------------------- METHODS ----------------------------------*/

void	User::activateAuth()
{
	if (pass_auth.size() && username.size() && nickname.size())
		this->connected = 1;
}

/*** --------------------------------- ACCESSOR ---------------------------------*/

/*** --------------------------------- ACEPTION ---------------------------------*/

