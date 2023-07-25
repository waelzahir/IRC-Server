/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 00:02:54 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/24 22:37:31 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Server.hpp"
#include "ReqParser.hpp"
#include <netdb.h>


void   getActivity(Server *server, std::string &def)
{
  int index = rand() % server->activities.size();
  def = server->activities[index];   
}
static void getBotEntry(Server *server ,std::string &def, std::string bot)
{
    if (bot == "bored")
        {
             getActivity(server, def);
             return ;
        }
}
void	Commands::bot(Client *client, std::stringstream &stream)
{
    ReqParser parser(stream);
    Message message(*client, "PRIVMSG", "IRCSERV.BOT");
    message.set_param(client->_client_user.nickname);
    std::string def("Usage -> BOT bored");
    if (parser.getStatus())
    {
        std::pair<int, std::string> what = parser.getToken();
        getBotEntry(_server, def, what.second);
    }
    message.set_trailing(def);
    _server->sendMessage(message, *client);
    message.clear_final();
}
