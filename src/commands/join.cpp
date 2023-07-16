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

std::queue<std::pair<std::string, std::string>> get_channels_key(std::stringstream &stream)
{
	std::queue<std::pair<std::string, std::string>> map_ch;
	std::stringstream channles;
	std::stringstream keys;

	stream >> channles;
	stream >> keys;
	while (!channles.eof())
		map_ch.push(std::make_pair(extract_token(channles), extract_token(keys)));
	return map_ch;
}

void find_channel_add_user(Channel &channel, std::vector<Channel> &channels, Message& message)
{
	int status = (*find(channels.begin(), channels.end(), channel))
					 .add_user(*channel._owner, channel._key);
	if (status == 1) // key invalid
		;
	else if (status == 2) // user already in channel
		;
}

void Commands::join(Client *client, std::stringstream &_stream)
{
	std::queue<std::pair<std::string, std::string>> channells;
	channells = get_channels_key(_stream);
	Message message(*client,"JOIN",client->_client_user.nickname);

	while (channells.size())
	{
		Channel new_channel(channells.front().first);
		new_channel._owner = &client->_client_user;
		new_channel._key = channells.front().second;
		if (_server->createChannel(new_channel))
		{
			// channel exist
		}
		// channel not exist
		find_channel_add_user(new_channel, _server->channels, message);
		message.set_param(new_channel._name);
		_server->sendMessage(message);
		channells.pop();
		message.clear_final();
	}
	// if (!message.length())
	// {
	// 	std::cout << "--------join ende-------" << std::endl;
	// 	return ;
	// }
}