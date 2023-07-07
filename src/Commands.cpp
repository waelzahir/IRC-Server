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


/*** --------------------------------- ACCESSOR ---------------------------------*/

/*** --------------------------------- ACEPTION ---------------------------------*/

