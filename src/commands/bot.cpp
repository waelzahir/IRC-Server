/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 00:02:54 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/24 00:31:25 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Server.hpp"
#include "ReqParser.hpp"

static void getBotEntry(std::string &def, std::string bot)
{
    // def = bot;
}
void	Commands::bot(Client *client, std::stringstream &stream)
{
    ReqParser parser(stream);
    Message message(*client, "PRIVMSG", "IRCSERV.BOT");
    message.set_param(client->_client_user.nickname);
    std::string def("no such BOT");
    if (parser.getStatus())
    {
        std::pair<int, std::string> what = parser.getToken();
        getBotEntry(def, what.second);
    }
    message.set_trailing(def);
    _server->sendMessage(message, *client);
    message.clear_final();
}
