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
	if (((*it).second).get_mode_status(I_MODE) )
	{
		std::set<std::string>::iterator itt = ((*it).second).inveted.find(message._sender._client_user.nickname);
		if(itt == ((*it).second).inveted.end() )
			throw std::string("not invited");
		else
			((*it).second).inveted.erase(itt);
	}
	if (((*it).second).get_mode_status(L_MODE) && (int)((*it).second)._users.size() >= ((*it).second)._user_limit)
	{
		throw std::string("limits");
	}
	int status = (*it).second.add_user(message._sender._client_user, channel._key);
	
	if (status == 1) // key invalid
		throw std::string("key invalid");
	else if (status == 2)
		throw std::string("user already in channel");
	return (*it).second;
}

static bool check_channel_name(std::string& channel)
{
	if (channel.empty())
		return false;
	if (channel[0] != '#' && channel[0] != '&')
		return false;
	std::string::iterator it;

	for (it =  channel.begin() + 1 ; it != channel.end() ; it++)
	{
		if (!isalpha(*it) && !isalnum(*it))
			return false;
	}
	return true;
}
void Commands::join(Client *client, std::stringstream &_stream)
{

	std::queue<std::pair<std::string, std::string> > channells;
	channells = get_channels_key(_stream);
	Message message(*client, "JOIN", client->_client_user.nickname + "!" + client->_client_user.username + "@" + client->host);
	int sts = -1;

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
		if (check_channel_name(channells.front().first))
			sts = _server->createChannel(new_channel);
		try
		{
			if (!check_channel_name(channells.front().first))
				throw std::string("invalid name of channnel");
			Channel &channel = find_channel_add_user(new_channel, _server->channels, message);
			if (!channel._key.empty())
				channel.set_mode(K_MODE);
			message.set_param(new_channel._name);
			_server->sendMessage(message);
			if (!sts)
			{
				message.clear_final();
				channel._users.at(0).owner = 1; 
				channel._topic_seter = client->_client_user.nickname; 
				// channel not exist
			}
			else
				_server->sendMessageChannel(message, channel._name);
			message.set_message_error(RPL_CREATIONTIME(_server->serverName, client->_client_user.nickname ,channel._name, "222"));
			_server->sendMessage_err(message);
			message.set_message_error(RPL_CHANNELMODEIS(_server->serverName, client->_client_user.nickname ,channel._name, "+o",""));
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
			else if (e == "invalid name of channnel")
			{
				message.set_message_error(ERR_BADCHANNAME(_server->serverName, client->_client_user.nickname ,new_channel._name));
				_server->sendMessage_err(message);
			}
		}
		channells.pop();
	}
}