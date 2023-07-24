/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 00:02:54 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/24 18:53:00 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Server.hpp"
#include "ReqParser.hpp"
#include <netdb.h>


void   getJoke(std::string &def)
{
    std::string message_fmt = "GET / HTTP/1.1\r\nHost: icanhazdadjoke.com\r\nUser-Agent: curl/7.64.1\r\nAccept: application/json\r\n\r\n";
    std::cout << message_fmt ;
    struct hostent *host;
    struct  sockaddr_in ad;
    int sock;
    host = gethostbyname("www.icanhazdadjoke.com");
    if (!host)
    {
        def = "couldnt resolve host";
        return ;
    }
    bzero(&ad, sizeof (ad));
    ad.sin_family = AF_INET;
    ad.sin_port = htons(80);
    memcpy(&ad.sin_addr.s_addr , host->h_addr,host->h_length);
    sock =  socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        def = "error creating socket";
        return ;
    }
    if (connect(sock, (struct sockaddr *)&ad, sizeof(ad) ) == -1)
    {
        def = "coudn't conect to host";
        return ;
    }
    def = "succes";
    send(sock,message_fmt.c_str(), message_fmt.length(), 0);
    char    buffer[1024];
    bzero(buffer, 1024);
    recv(sock, buffer, 1000, 0);
    std::cout << buffer << std::endl;
    
}
static void getBotEntry(std::string &def, std::string bot)
{
    if (bot == "joke")
        {
             getJoke(def);
             return ;
        }
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
