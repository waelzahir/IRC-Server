#include "Message.hpp"

/*** ------------------------------- CONSTRUCTOR --------------------------------*/




Message::Message(Client	&sender, const char *command) :_sender(sender), _source(""), 
	_tag(""),
	_command(command),
	_param(""),
	_trailing(""),
	crlf("\r\n")
{
}
Message::Message(Client	&sender, const char *command, std::string source) :_sender(sender), _source(source), _tag(""), _command(command), _param(""),  _trailing(""), crlf("\r\n")
{
}

Message::Message(const Message &other) : _sender(other._sender)
{
	
	*this = other;
}

/*** -------------------------------- DESTRUCTOR --------------------------------*/
Message::~Message()
{
}

/*** --------------------------------- OVERLOAD ---------------------------------*/
Message &Message::operator=(Message const &other)
{
	_final_message = other._final_message;
	_source = other._source;
	_tag = other._tag;
	_command = other._command;
	_param = other._param;
	_sender = other._sender;
	_trailing = other._trailing;
	crlf = other.crlf;
	return *this;
}

/*** --------------------------------- METHODS ----------------------------------*/
void Message::add_param(std::string &param)
{
	if (_param != "")
	{
		param += ",";
	}
	_param += param;
}
void Message::set_param(std::string &param)
{
	_param = param;
}
void Message::set_source(std::string &source)
{
	_source = source;
}
void Message::set_command(std::string &command)
{
	_command = command;
}
void Message::set_trailing(std::string &trailing)
{
	_trailing = trailing;
}
void Message::set_tag(std::string &tag)
{
	_tag = tag;
}
void Message::set_message()
{
	if (_tag != "")
		_final_message = "@" + _tag + " ";
	if (_source != "")
		_final_message = _final_message + ":" + _source + " ";
	_final_message = _final_message  + _command;
	if (_param != "")
		_final_message = _final_message + " " + _param;	
	if (_trailing != "")
		_final_message = _final_message + " :" + _trailing;
	_final_message =  _final_message + "\r\n";
}
void Message::set_message_error(const std::string &error)
{
	_final_message = error + "\r\n";
}

size_t Message::size()
{
	return _final_message.length();
}

void Message::clear_final() 
{
	_tag = "";
	_param = "";
	_final_message = "";
	_trailing = "";
}
/*** --------------------------------- ACCESSOR ---------------------------------*/

/*** --------------------------------- ACEPTION ---------------------------------*/
