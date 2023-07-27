#include "User.hpp"

// int 		connected;
// 	int 		welcomed;
// 	int 		owner;
// 	std::string username;
// 	std::string nickname;
// 	std::string pass_auth;
/*** ------------------------------- CONSTRUCTOR --------------------------------*/
User::User(): connected(0), welcomed(1), owner(-1), username(""), nickname(""), pass_auth("")
{
}
User::User(std::string _u, std::string _n) :connected(0), welcomed(1), owner(-1),  username(_u), nickname(_n), pass_auth("")
{
}

User::User(const User &other)
{
	*this = other;
}

/*** -------------------------------- DESTRUCTOR --------------------------------*/
User::~User()
{
}

/*** --------------------------------- OVERLOAD ---------------------------------*/
User&   User::operator=(User const & other )
{
	this->nickname = other.nickname;
	this->username = other.username;
	this->welcomed = other.welcomed;
	this->connected = other.connected;
	this->pass_auth = other.pass_auth;
	this->owner = other.owner;
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

