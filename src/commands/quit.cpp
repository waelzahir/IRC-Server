/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 21:13:46 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/27 01:54:35 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Server.hpp"

void	Commands::quit(Client *client, std::stringstream &stream)
{
    std::string reason;
    std::string buffer; 
    while (!stream.eof())
    {
        stream >> buffer;
        reason += buffer + " ";
    }
    if (reason.length() && reason[0] == ':')
        reason.erase(0,1);
    Message message(*client, "QUIT", client->_client_user.nickname);
    if (reason.length())
        message.set_trailing(reason);
    _server->sendMessage(message, *client);
    close(client->fd);
    _server->removeClient(client);
    message.clear_final();
}
