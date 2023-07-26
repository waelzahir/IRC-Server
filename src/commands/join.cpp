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

std::queue<std::pair<std::string, std::string> > get_channels_key(std::stringstream &stream)
{
	std::queue<std::pair<std::string, std::string> > map_ch;
	std::stringstream channles;
	std::stringstream keys;

	stream >> channles;
	stream >> keys;
	while (!channles.eof())
		map_ch.push(std::make_pair(extract_token(channles), extract_token(keys)));
	return map_ch;
}

Channel& find_channel_add_user(Channel &channel, std::map<std::string, Channel> &channels, Message& message)
{

	std::map<std::string, Channel>::iterator it = channels.find(channel._name); 
	if (((*it).second).get_mode_status(I_MODE) && ((*it).second).inveted.find(message._sender._client_user.nickname) == ((*it).second).inveted.end() )
	{
		throw std::string("not invited");
	}
	if (((*it).second).get_mode_status(L_MODE) && ((*it).second)._users.size() >= ((*it).second)._user_limit)
	{
		throw std::string("limits");
	}
	int status = (*it).second.add_user(message._sender._client_user, channel._key);
	
	if (status == 1) // key invalid
		throw std::string("key invalid");
	else if (status == 2) // user already in channel
		throw std::string("user already in channel");
	return (*it).second;
}

void Commands::join(Client *client, std::stringstream &_stream)
{

	std::queue<std::pair<std::string, std::string> > channells;
	channells = get_channels_key(_stream);
	Message message(*client, "JOIN", client->_client_user.nickname + "!" + client->_client_user.username + "@" + client->host);

	// Message message(*client,"JOIN",client->_client_user.nickname);
	if (!channells.size())
	{
		message.set_message_error(ERR_NEEDMOREPARAMS(_server->serverName, client->_client_user.nickname, "JOIN"));
		_server->sendMessage(message);
	}

	while (channells.size())
	{
		Channel new_channel(channells.front().first);
		// new_channel._owner = &client->_client_user;
		new_channel._key = channells.front().second;
		int sts = _server->createChannel(new_channel);
		try
		{
			Channel &channel = find_channel_add_user(new_channel, _server->channels, message);
			if (!channel._key.empty())
				channel.set_mode(K_MODE);
			message.set_param(new_channel._name);
			_server->sendMessage(message);
			if (!sts)
			{
				message.clear_final();
				channel._users.at(0).owner = 1; 
				// channel not exist
			}
			else
				_server->sendMessageChannel(message, channel._name);
			message.set_message_error(RPL_CREATIONTIME(_server->serverName, client->_client_user.nickname ,channel._name, "222"));
			std::cout << "|" <<message._final_message << "|" << std::endl;
			_server->sendMessage_err(message);
			message.set_message_error(RPL_CHANNELMODEIS(_server->serverName, client->_client_user.nickname ,channel._name, "+o",""));
			std::cout << "|" <<message._final_message << "|" << std::endl;
			_server->sendMessage_err(message);
			message.set_message_error(RPL_TOPIC(_server->serverName,client->_client_user.nickname ,new_channel._name, channel._topic));
			_server->sendMessage_err(message);
			message.set_message_error(RPL_NAMREPLY(_server->serverName,client->_client_user.nickname ,new_channel._name,channel.get_channels_users()));
			_server->sendMessage_err(message);
			message.set_message_error(RPL_ENDOFNAMES(_server->serverName,client->_client_user.nickname ,new_channel._name));
			_server->sendMessage_err(message);
		}
		catch(std::string& e)
		{
			std::cout << e <<std::endl;
			if (e == "key invalid")
			{
				message.set_message_error(ERR_BADCHANNELKEY(_server->serverName,client->_client_user.nickname ,new_channel._name));
				_server->sendMessage_err(message);
			}
			else if (e == "not invited")
			{
				message.set_message_error(ERR_INVITEONLYCHAN(_server->serverName,client->_client_user.nickname ,new_channel._name));
				_server->sendMessage_err(message);
			}
			else if (e == "limits")
			{
				message.set_message_error(ERR_CHANNELISFULL(_server->serverName, client->_client_user.nickname ,new_channel._name));
				_server->sendMessage_err(message);
			}
			// else if (e == "user already in channel")
			// {
			// 	// do nothing
			// }
		}
		channells.pop();
	}
}