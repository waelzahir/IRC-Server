/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 21:13:46 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/21 21:30:51 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Server.hpp"
#include "ReqParser.hpp"

void	Commands::quit(Client *client, std::stringstream &stream)
{
    ReqParser parser(stream);
    Message message(*client, "QUIT", client->_client_user.nickname);
    if (!parser.getStatus())
    {
        _server->sendMessage(message, *client);
        return; 
    }
    std::pair<int, std::string> what = parser.getToken();
    message.set_trailing(what.second);
    _server->sendMessage(message, *client);
    close(client->fd);
    _server->removeClient(client);
    message.clear_final();
}
