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
	src >> temp;

	return temp;
}
static std::string extract_token_args(std::stringstream &src, std::string &mod)
{
	std::string args;

	if (src.eof())
		return std::string("");
	while (!src.eof())
	{
		std::string temp;
		src >> temp;

		if (temp[0] == '+' || temp[0] == '-')
		{
			mod = temp;
			break;
		}
		if (args != "")
			args += " ";
		args += temp;
	}
	return args;
}

void Commands::check_channel(std::string &channel)
{
	if (!channel.size())
		throw std::string("ERR_NEEDMOREPARAMS");
	try
	{
		_server->channels.at(channel);
	}
	catch(const std::exception& e)
	{
		throw std::string("ERR_NOSUCHCHANNEL");
	}
	
}
void check_modestring(std::string &op)
{
	size_t size = op.size();
	if (!size)
		return ;
	if ((op.at(0) != '+' && op.at(0) != '-') || op.size() < 2)
		throw std::string("RPL_CHANNELMODEIS");
	std::string ops = "oiktl+-";
	for (int i = 1; op[i] ; i++)
	{
		// if ((op.at(i) == '-' || op.at(i) == '+') && (i != size -1 && isalpha(op.at(i + 1))))
		// 	throw std::string("RPL_CHANNELMODEIS");
		if (ops.find(op.at(i)) == ops.npos)
			throw std::string("RPL_CHANNELMODEIS");
	}
}



typedef void (*optr)(std::string&);


void mode_o(std::string &)
{

}

optr get_option(char op)
{
	std::map<char, optr> commands;


	commands['o'] = &mode_o;
	std::cout << op << std::endl;

	try
	{
		return commands.at(op);
	}
	catch(const std::exception& e)
	{
    	return NULL;
	}
}


void get_params(std::queue<std::pair<std::string, std::string> > &map_param, std::stringstream &stream)
{
	std::string mod;
	while (!stream.eof())
	{
		std::string modestring;
		if (!mod.empty())
		{
			modestring = mod;
			mod = "";
		}
		else
			modestring = extract_token(stream);

		std::string mode_arguments = extract_token_args(stream, mod);
		check_modestring(modestring);
		map_param.push(std::make_pair(modestring, mode_arguments));
	}
	if (!mod.empty())
	{
		std::string modestring;
		std::cout << "enter" << std::endl;
		modestring = mod;
		mod = "";

		std::string mode_arguments = extract_token_args(stream, mod);
		map_param.push(std::make_pair(modestring, mode_arguments));
	}
}


void	Commands::mode(Client *client, std::stringstream &stream)
{
	Message message(*client, "MODE", client->_client_user.nickname);
	std::queue<std::pair<std::string, std::string> > map_param;
	std::string channel;

	stream >> channel;
	try
	{
		check_channel(channel);
		get_params(map_param, stream);
		while (map_param.size())
		{
			map_param.pop();
		}
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