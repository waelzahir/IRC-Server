#include "Commands.hpp"




static std::stringstream& operator>> (std::stringstream& src, std::stringstream& dst)
{
	std::string temp;
    
    src >> temp;
    dst << temp;
    return dst;
}

static std::string extract_token(std::stringstream& src)
{
	std::string temp;

    if (src.eof())
        return std::string("");
    getline(src, temp, ',');
    return temp;
}

std::queue<std::pair <std::string, std::string> > get_channels_key(std::stringstream &stream)
{
	std::queue<std::pair <std::string, std::string> > map_ch;
    std::stringstream channles;
    std::stringstream keys;

    stream >> channles;
    stream >> keys;
    while (!channles.eof())
        map_ch.push(std::make_pair(extract_token(channles), extract_token(keys)));
	return map_ch;
}



void	Commands::join(Client *client, std::stringstream &_stream)
{
	std::cout << "--------join start-------" << std::endl;
	std::queue<std::pair <std::string, std::string> > channells;
	channells = get_channels_key(_stream);
	while (channells.size())
	{
		Channel new_channel(channells.front().first);
		new_channel._owner = &client->_client_user;
		if (_server->createChannel(new_channel))
		{
			int status = (*find(_server->channels.begin(),_server->channels.end(), new_channel))\
				.add_user(client->_client_user, channells.front().second);
			if (status == 1)
				; // key invalis
			else if (status == 2)
				;// user already in channel
			// sucsess

		}
		channells.pop();
	}
}