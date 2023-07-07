#include "Message.hpp"

/*** ------------------------------- CONSTRUCTOR --------------------------------*/
Message::Message()
{
	std::cout << "Message Constructor called" << std::endl;
}

Message::Message(const Message &other)
{
	*this = other;
}

/*** -------------------------------- DESTRUCTOR --------------------------------*/
Message::~Message()
{
	std::cout << "Message Destructor called" << std::endl;
}

/*** --------------------------------- OVERLOAD ---------------------------------*/
Message&   Message::operator=(Message const & other )
{
	(void)other;
	return *this;
}

/*** --------------------------------- METHODS ----------------------------------*/


/*** --------------------------------- ACCESSOR ---------------------------------*/

/*** --------------------------------- ACEPTION ---------------------------------*/

