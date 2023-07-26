/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 00:02:54 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/26 21:48:40 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Server.hpp"
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
    std::string bot;
    stream >> bot;
    Message message(*client, "NOTICE", "BoredBot");
    std::string name("BoredBot");
    message.set_param(name);
    std::string def("Usage -> BOT bored");
    if (bot.length())
    {
        getBotEntry(_server, def, bot);
    }
    message.set_trailing(def);
    _server->sendMessage(message, *client);
    message.clear_final();
    std::cout <<"reach" << std::endl;
}
