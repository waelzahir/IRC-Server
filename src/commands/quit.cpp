/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 21:13:46 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/26 21:47:20 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Server.hpp"

void	Commands::quit(Client *client, std::stringstream &stream)
{
    std::string reason;
    stream >> reason;
    Message message(*client, "QUIT", client->_client_user.nickname);
    if (reason.length())
        message.set_trailing(reason);
    _server->sendMessage(message, *client);
    close(client->fd);
    _server->removeClient(client);
    message.clear_final();
}
