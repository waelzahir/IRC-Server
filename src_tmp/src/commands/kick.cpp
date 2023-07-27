# include <Commands.hpp>




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



void Commands::kick(Client *client, std::stringstream &_stream)
{
	std::string channel;
	std::string msg;
	User *c_user;
	_stream >> channel;
	Message message(*client,"KICK", client->_client_user.nickname);
	Message err(*client, "KICK");
	try
	{
		Channel &ch = check_channel(channel);	
		if (!ch.is_operator(client->_client_user))
			throw std::string("ERR_CHANOPRIVSNEEDED");
		std::stringstream users;
		_stream >> users;
		_stream >> msg;
		while (!users.eof())
		{
			std::string user;
			user = extract_token(users);
			try
			{
				c_user = ch.get_user(user);
				if (c_user == NULL)
					throw std::string("ERR_USERNOTINCHANNEL");
				message.add_param_space(channel);
				message.add_param_space(user);
				if (!msg.empty())
					message.add_param_space(msg);
				_server->sendMessage(message);
				_server->sendMessageChannel(message, channel);
				message.clear_final();
				ch.remove_user(*c_user);
			}
			catch(std::string& e)
			{
				if (e == "ERR_USERNOTINCHANNEL")
				{
					err.set_message_error(ERR_USERNOTINCHANNEL(_server->serverName, client->_client_user.nickname , user,channel));
					_server->sendMessage_err(err);
				}
				message.clear_final();
			}
		}
	}
	catch(std::string &e)
	{
		if (e == "ERR_NOSUCHCHANNEL")
		{
			message.set_message_error(ERR_NOSUCHCHANNEL(_server->serverName, client->_client_user.nickname ,channel));
			_server->sendMessage_err(message);
		}
		else if (e == "ERR_NEEDMOREPARAMS")
		{
			message.set_message_error(ERR_NEEDMOREPARAMS(_server->serverName, client->_client_user.nickname ,"KICK"));
			_server->sendMessage_err(message);
		}
		else if (e == "ERR_CHANOPRIVSNEEDED")
		{
			message.set_message_error(ERR_CHANOPRIVSNEEDED(_server->serverName, client->_client_user.nickname ,channel));
			_server->sendMessage_err(message);
		}
	}

	
}