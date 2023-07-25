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

static std::string extract_options(std::string &_src)
{
	std::string temp;

	if (_src.empty())
		return std::string(); // maybe do in upper layer 
	
	std::string src = _src;
	src = *(src.begin() + 1);
	size_t pos = src.find_first_of("+-");
	temp = _src.substr(0 , pos);
	if (pos == src.npos)
		return  _src = "", temp;
	_src.erase(_src.begin(), _src.begin() + pos);
	return temp;
}

static char extract_option(std::string &src, char& sign)
{
	char temp;
	int offset = 1;

	temp = src[1];
	src[1] = src[0];
	sign =  src[0];
	if (src.size() >= 3 && (src[2] == '+' || src[2] == '-'))
		offset++;
	src.erase(src.begin(), src.begin() + offset);
	return temp;
}

static std::string extract_argument(std::string &src)
{
	std::string temp;
	std::stringstream stream;

	if (src.empty())
		return std::string(); // maybe do in upper layer 
	stream  << src;
	stream >> temp;
	src.clear(); 
	getline(stream, src);
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


Channel& Commands::check_channel(std::string &channel)
{
	if (!channel.size())
		throw std::string("ERR_NEEDMOREPARAMS");
	std::map<std::string, Channel>::iterator it;

	it = _server->channels.find(channel);
	if (it == _server->channels.end())
	{
		throw std::string("ERR_NOSUCHCHANNEL");
	}
	return (*it).second;
}

void check_modestring(std::string &op)
{
	size_t size = op.size();
	if (!size)
		return ;
	if (op.at(0) != '-' && op.at(0) != '+')
		throw std::string("RPL_CHANNELMODEIS");
	if ((op.at(0) != '+' && op.at(0) != '-') || op.size() < 2)
		throw std::string("RPL_CHANNELMODEIS");
	std::string ops = "oiktl+-";
	for (int i = 1; op[i] ; i++)
	{
		if ((op.at(i) == '-' || op.at(i) == '+') && (i == size - 1 || !isalpha(op.at(i + 1))))
			throw std::string("RPL_CHANNELMODEIS");
		if (ops.find(op.at(i)) == ops.npos)
			throw std::string("RPL_CHANNELMODEIS");
	}
}


optr get_option(char op)
{
	std::map<char, optr> commands;


	commands['i'] = &Commands::mode_i;
	commands['t'] = &Commands::mode__t;
	commands['k'] = &Commands::mode_k;
	commands['o'] = &Commands::mode_o;
	commands['l'] = &Commands::mode_l;

	try
	{
		return commands.at(op);
	}
	catch(const std::exception& e)
	{
    	return NULL;
	}
}

void get_params(std::pair<std::string, std::string> &map_param, std::stringstream &stream)
{
	std::string mod;
	std::string modestring;
	
	modestring = extract_token(stream);
	std::string mode_arguments = extract_token_args(stream, mod);
	check_modestring(modestring);
	map_param = std::make_pair(modestring, mode_arguments);
}


void  Commands::get_option_and_args(Channel& channel, User &user, std::pair<std::string, std::string> & map_param)
{
	char sign;
	std::string args_left;

	sign = 0;
	while (!map_param.first.empty())
	{
		std::string new_str = extract_options(map_param.first);
		while (new_str.size() > 1)
		{
			optr modeptr = get_option(extract_option(new_str, sign));

			if (modeptr != NULL)
			{
				args_left = (this->*modeptr)(channel, user, extract_argument(map_param.second),sign);
				if (!args_left.empty())
				{
					map_param.second = args_left + " " + map_param.second;
				}
			}
		}
	}
}


void	Commands::mode(Client *client, std::stringstream &stream)
{
	Message message(*client, "MODE", client->_client_user.nickname);
	std::pair<std::string, std::string> pair_param;
	std::string channel;
	std::string time;

	stream >> channel;
	
	std::cout << stream.str() << std::endl;
	try
	{
		Channel& ch = check_channel(channel);
		get_params(pair_param, stream);
		if (pair_param.first.empty())
		{
			time = ch._create_time;
			throw  std::string("RPL_CREATIONTIME");
		}
		msg_tmp = &message;
		get_option_and_args(ch , client->_client_user , pair_param);

	}
	catch(std::string& e)
	{
		if (e == "ERR_UMODEUNKNOWNFLAG")
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
		else if (e == "ERR_CHANOPRIVSNEEDED")
		{
			message.set_message_error(ERR_CHANOPRIVSNEEDED(_server->serverName, client->_client_user.nickname ,channel));
			_server->sendMessage_err(message);
		}
		else if (e == "RPL_CREATIONTIME")
		{
			message.set_message_error(RPL_CREATIONTIME(_server->serverName, client->_client_user.nickname ,channel, time));
			_server->sendMessage_err(message);
		}
	}
}