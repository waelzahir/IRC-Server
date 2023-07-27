/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 00:02:34 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/27 01:53:49 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Server.hpp"

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

void	Commands::part(Client *client, std::stringstream &stream)
{
    	Message message(*client,"PART", client->_client_user.nickname);
	    Message err(*client, "PART");
   		std::stringstream channels;
        std::string msg;
        std::string buffer; 

        stream >> channels;
        while (!stream.eof())
        {
            stream >> buffer;
            msg += buffer + " ";
        }
        if (msg.length() && msg[0] == ':')
            msg.erase(0,1);
        while (!channels.eof())
        {

            std::string channelname = extract_token(channels);
            try
            {
                if (channelname.length() ==1 && channelname[0] == ':')
                    throw std::string("ERR_NEEDMOREPARAMS");
                Channel &channelref  = check_channel(channelname);
                User *userptr = channelref.get_user(client->_client_user.nickname);
                if (!userptr)
                    throw std::string("ERR_NOTONCHANNEL");
                message.set_param(channelname);
                message.set_trailing(msg);
                _server->sendMessage(message);
                _server->sendMessageChannel(message, channelname);
                channelref.remove_user(*userptr);
                message.clear_final();    
                if (!channelref._users.size())
                {
                    _server->removeChannel(channelref);
                }
                
            }
            catch(std::string  &e)
            {
                if (e == "ERR_NOSUCHCHANNEL")
		        {
		    	    err.set_message_error(ERR_NOSUCHCHANNEL(_server->serverName, client->_client_user.nickname ,channelname));
			        _server->sendMessage_err(err);
		        }
                if (e == "ERR_NOTONCHANNEL")
                {
                    err.set_message_error(ERR_NOTONCHANNEL(_server->serverName, client->_client_user.nickname ,channelname));
                    _server->sendMessage_err(err);
                }
                	else if (e == "ERR_NEEDMOREPARAMS")
		        {
			        message.set_message_error(ERR_NEEDMOREPARAMS(_server->serverName, client->_client_user.nickname ,"PART"));
			        _server->sendMessage_err(message);
		        }
                message.clear_final();                
            }
            
        }
}   
