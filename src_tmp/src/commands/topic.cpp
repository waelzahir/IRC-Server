# include <Commands.hpp>


static std::string get_time_str(std::time_t &t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}
void Commands::topic(Client *client, std::stringstream &_stream)
{
	Message message(*client, "TOPIC", client->_client_user.nickname);
	std::string topic_msg;
	std::string channel;


	_stream >> channel;
	_stream >> topic_msg;

	try
	{
		Channel &ch = check_channel(channel);
		if (topic_msg.empty())
		{
			message.set_message_error(RPL_TOPIC(_server->serverName,client->_client_user.nickname ,channel, ch._topic));
			_server->sendMessage_err(message);
			message.set_message_error(RPL_TOPICWHOTIME(_server->serverName, client->_client_user.nickname ,channel,ch._topic_seter, get_time_str(ch._topic_time)));
			throw std::string("RPL_TOPICWHOTIME");
		}
		if ((!ch.is_operator(client->_client_user) && ch.get_mode_status(T_MODE)))
			throw std::string("ERR_CHANOPRIVSNEEDED");
		if (topic_msg.empty() && ch._topic.empty())
		{
			throw std::string("RPL_NOTOPIC");
		}
		topic_msg.erase(0,1);
		ch._topic = topic_msg;
		ch._topic_seter = client->_client_user.nickname;
		ch._topic_time =  std::time(NULL);
		message.set_message_error(RPL_TOPIC(_server->serverName,client->_client_user.nickname ,channel, ch._topic));
		_server->sendMessage_err(message);
		_server->sendMessageChannel_err(message,ch._name);
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
			message.set_message_error(ERR_NEEDMOREPARAMS(_server->serverName, client->_client_user.nickname ,"KICK"));
			_server->sendMessage_err(message);
		}
		else if (e == "ERR_CHANOPRIVSNEEDED")
		{
			message.set_message_error(ERR_CHANOPRIVSNEEDED(_server->serverName, client->_client_user.nickname ,channel));
			_server->sendMessage_err(message);
		}
		else if (e == "RPL_NOTOPIC")
		{
			
			message.set_message_error(RPL_NOTOPIC(_server->serverName, client->_client_user.nickname ,channel));
			_server->sendMessage_err(message);
		}
		else if (e == "RPL_TOPICWHOTIME")
		{
			
			_server->sendMessage_err(message);
		}
	}	
}
