# include <Commands.hpp>




void Commands::	invite(Client *client, std::stringstream &_stream)
{
	Message message(*client, "INVITE", client->_client_user.nickname);
	std::string nickname;
	std::string channel;
	std::string append;

	_stream >> nickname;
	_stream >> channel;

	try
	{
		Channel &ch = check_channel(channel);
		if (!ch.is_operator(client->_client_user))
			throw std::string("ERR_CHANOPRIVSNEEDED");
		if (nickname.empty())
			throw std::string("ERR_NEEDMOREPARAMS");
		if (ch.get_user(nickname))
			throw std::string("ERR_USERONCHANNEL");
		ch.inveted.insert(nickname);
		message.set_message_error(RPL_INVITING(_server->serverName, client->_client_user.nickname ,channel, nickname));
		_server->sendMessage_err(message);
	}
	catch(std::string e)
	{
		if (e == "ERR_NOSUCHCHANNEL")
		{
			message.set_message_error(ERR_NOSUCHCHANNEL(_server->serverName, client->_client_user.nickname ,channel));
			_server->sendMessage_err(message);
		}
		else if (e == "ERR_NEEDMOREPARAMS")
		{
			message.set_message_error(ERR_NEEDMOREPARAMS(_server->serverName, client->_client_user.nickname ,"INVITE"));
			_server->sendMessage_err(message);
		}
		else if (e == "ERR_CHANOPRIVSNEEDED")
		{
			message.set_message_error(ERR_CHANOPRIVSNEEDED(_server->serverName, client->_client_user.nickname ,channel));
			_server->sendMessage_err(message);
		}
		else if (e == "ERR_USERONCHANNEL")
		{
			message.set_message_error(ERR_USERONCHANNEL(_server->serverName, client->_client_user.nickname ,nickname,channel));
			_server->sendMessage_err(message);
		}
	}
}