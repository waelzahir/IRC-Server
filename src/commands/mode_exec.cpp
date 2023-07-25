#include "Commands.hpp"

std::string Commands::mode_i(Channel &channel, User &user, const std::string &str, char sign)
{
	if (!channel.is_operator(user))
		throw std::string("ERR_CHANOPRIVSNEEDED");
	
	if (sign == '-' && channel.get_mode_status(I_MODE))
	{
		channel.unset_mode(I_MODE);
		
		msg_tmp->set_message_error(RPL_CHANNELMODEIS(_server->serverName,msg_tmp->_source, channel._name, "-i",""));
		_server->sendMessage_err(*msg_tmp);
	}
	else if (sign == '+' && !channel.get_mode_status(I_MODE))
	{
		msg_tmp->set_message_error(RPL_CHANNELMODEIS(_server->serverName,msg_tmp->_source, channel._name, "+i",""));
		_server->sendMessage_err(*msg_tmp);
		channel.set_mode(I_MODE);
	}
	return str;
}
std::string Commands::mode__t(Channel &channel, User &user, const std::string &str, char sign)
{
	if (!channel.is_operator(user))
		throw std::string("ERR_CHANOPRIVSNEEDED");
	if (sign == '-' && channel.get_mode_status(T_MODE))
	{
		channel.unset_mode(T_MODE);
		
		msg_tmp->set_message_error(RPL_CHANNELMODEIS(_server->serverName,msg_tmp->_source, channel._name, "-t",""));
		_server->sendMessage_err(*msg_tmp);
	}
	else if (sign == '+' && !channel.get_mode_status(T_MODE))
	{
		msg_tmp->set_message_error(RPL_CHANNELMODEIS(_server->serverName,msg_tmp->_source, channel._name, "+t",""));
		_server->sendMessage_err(*msg_tmp);
		channel.set_mode(T_MODE);
	}
	return str;
}

std::string Commands::mode_k(Channel &channel, User &user, const std::string &str, char sign)
{
	if (!channel.is_operator(user))
		throw std::string("ERR_CHANOPRIVSNEEDED");
	if (sign == '-' && channel.get_mode_status(K_MODE))
	{
		channel.unset_mode(K_MODE);
		channel._key = "";
		msg_tmp->clear_final();
		msg_tmp->set_big_param(channel._name + " -k *");
		_server->sendMessage(*msg_tmp);
		_server->sendMessageChannel(*msg_tmp, channel._name);
		return str;
	}
	else if (sign == '+')
	{
		if (str.empty())
			return str;
		msg_tmp->clear_final();
		msg_tmp->set_big_param(channel._name + " +k " + str);
		_server->sendMessage(*msg_tmp);
		_server->sendMessageChannel(*msg_tmp, channel._name);
		channel._key = str;
		channel.set_mode(K_MODE);
		return "";
	}
	return str;
}
std::string Commands::mode_o(Channel &channel, User &user, const std::string &str, char sign)
{
	if (!channel.is_operator(user))
		throw std::string("ERR_CHANOPRIVSNEEDED");
	if (str.empty())
		return str;
	if (sign == '-')
	{
		User *cuser = channel.get_user(str);
		if (cuser == NULL || cuser->owner == -1)
			return "";
		cuser->owner = -1;
		msg_tmp->clear_final();
		msg_tmp->set_big_param(channel._name + " -o " + str);
		_server->sendMessage(*msg_tmp);
		_server->sendMessageChannel(*msg_tmp, channel._name);
	}
	else if (sign == '+')
	{
		User *cuser = channel.get_user(str);
		if (cuser == NULL || cuser->owner == 1)
			return "";
		cuser->owner = 1;
		msg_tmp->clear_final();
		msg_tmp->set_big_param(channel._name + " +o " + str);
		_server->sendMessage(*msg_tmp);
		_server->sendMessageChannel(*msg_tmp, channel._name);
	}
	return "";
}
static bool check_number(std::string str) {
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
    		return false;
    return true;
}

std::string Commands::mode_l(Channel &channel, User &user, const std::string &str, char sign)
{
	if (!channel.is_operator(user))
		throw std::string("ERR_CHANOPRIVSNEEDED");
	if (sign == '-' && channel.get_mode_status(L_MODE))
	{
		std::cout << "sign : " << sign << " str |" << str << "|" << std::endl;  
		channel.unset_mode(L_MODE);
		channel._user_limit = -1;
		msg_tmp->clear_final();
		msg_tmp->set_big_param(channel._name + " -l");
		_server->sendMessage(*msg_tmp);
		_server->sendMessageChannel(*msg_tmp, channel._name);
		return str;
	}
	else if (sign == '+')
	{
		if (!check_number(str))
			return "";
		if (str.empty())
			return str;
		msg_tmp->clear_final();
		msg_tmp->set_big_param(channel._name + " +l " + str);
		_server->sendMessage(*msg_tmp);
		_server->sendMessageChannel(*msg_tmp, channel._name);
		std::stringstream ss;
    	ss << str;
		ss >> channel._user_limit;
		channel.set_mode(L_MODE);
		return "";
	}
	return str;
}