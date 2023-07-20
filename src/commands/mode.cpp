#include "Commands.hpp"


static std::stringstream &operator>>(std::stringstream &src, std::stringstream &dst)
{
	std::string temp;

	src >> temp;
	dst << temp;
	return dst;
}

static std::string extract_token(std::stringstream &src)
{
	std::string temp;

	if (src.eof())
		return std::string("");
	getline(src, temp, ',');
	return temp;
}

void Commands::check_channel(std::string &channel)
{
	try
	{
		_server->channels.at(channel);
	}
	catch(const std::exception& e)
	{
		throw std::string("ERR_NOSUCHCHANNEL");
	}
	
}
void check_option(std::string &op)
{
	if (!op.size())
		return ;
	if ((op.at(0) != '+' && op.at(0) != '-') || op.size() < 2)
		throw std::string("RPL_CHANNELMODEIS");
	std::string ops = "oiktl";
	for (int i = 1; op[i] ; i++)
	{
		std::cout << "start : " << i << " " << op[i] << std::endl;
		if (ops.find(op.at(i)) == ops.npos)
			throw std::string("RPL_CHANNELMODEIS");
		std::cout << "end : " << std::endl;
	}
}

void Commands::check_parse(std::string &channel, std::string &option, std::string &param)
{
	if (!channel.size())
		throw std::string("ERR_NEEDMOREPARAMS");
	check_channel(channel);
	check_option(option);
}

void	Commands::mode(Client *client, std::stringstream &stream)
{
	Message message(*client, "MODE", client->_client_user.nickname);
	std::string channel;
	std::string option;
	std::string param;
	std::cout << "start : " << stream.str() << std::endl;


	stream >> channel;
	stream >> option;
	stream >> param;
	try
	{
		check_parse(channel, option, param);
			
	}
	catch(std::string& e)
	{

		if (e == "RPL_CHANNELMODEIS")
		{
			message.set_message_error(RPL_CHANNELMODEIS(_server->serverName,client->_client_user.nickname ,channel,"itkol","arguments" ));
			_server->sendMessage_err(message);
		}
		else if (e == "ERR_UMODEUNKNOWNFLAG")
		{
			message.set_message_error(ERR_UMODEUNKNOWNFLAG(_server->serverName,client->_client_user.nickname));
			_server->sendMessage_err(message);
		}
		else if (e == "ERR_NOSUCHCHANNEL")
		{
			message.set_message_error(ERR_NOSUCHCHANNEL(_server->serverName, client->_client_user.nickname ,channel));
			_server->sendMessage_err(message);
		}
		else if (e == "ERR_NEEDMOREPARAMS")
		{
			message.set_message_error(ERR_NEEDMOREPARAMS(_server->serverName, client->_client_user.nickname ,"MODE"));
			_server->sendMessage_err(message);
		}
	}
	
}