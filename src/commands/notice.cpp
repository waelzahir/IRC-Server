/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:55:51 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/26 20:17:37 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "Commands.hpp"
#include "Server.hpp"
#include "ReqParser.hpp"

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

static bool isChannel(std::string name)
{
    if (!name.length())
        return false;
    return (name[0] == '#' || name[0] == '&');
}
void Commands::notice(Client *client, std::stringstream &stream)
{
    std::stringstream destinations;
    std::string msg;
    stream >> destinations;
    stream >> msg;
    while (!destinations.eof())
    {
        Message message(*client, "NOTICE", client->_client_user.nickname + "!" + client->_client_user.username + "@" + client->host);
        std::string dest = extract_token(destinations);
        if (isChannel(dest))
        {
            try
            {
                Channel &chref = check_channel(dest);
                if (chref.get_user(client->_client_user) == NULL)
                    throw std::string(" ");
                message.set_param(dest);
                message.set_trailing(msg);
                _server->sendMessageChannel(message, dest);
                message.clear_final();
            }
            catch(std::string& e)
            {
                message.clear_final();
            }
            
        }
        else
        {
            try
            {
                message.set_param(dest);
                message.set_trailing(msg);
                _server->sendMessage(message, *this->_server->nickmak.at(dest));
                message.clear_final();
            }
            catch(...)
            {
                message.clear_final();
            }
        }

        
    }
}