#ifndef MACROS_H
# define MACROS_H

# define USERLEN 12


# define I_MODE 1
# define T_MODE (1 << 1)
# define K_MODE (1 << 2)
# define O_MODE (1 << 3)
# define L_MODE (1 << 4)

# define RPL_WELCOME(server, nick) server + " 001 "  + nick + " :Welcome to ircserver " + nick + "\r\n"
# define RPL_YOURHOST(server, port, nick) server + " 002 " + nick  + " :your host is ircserv at localhost:" + port + " running webserv vesrion 1\r\n"
# define RPL_CREATED(server, nick, day, month, year) server + " 003 "+ nick + " :this server was created " + day +  " " + month +  " " + year + "\r\n"
# define RPL_MYINFO(server , nick,modes) server + " 004 " + nick + " ircserv 1 " + modes + "\r\n"
# define RPL_ISUPPORT(server, nick) server + " 005 " + nick + " :are supported by this server\r\n"

# define ERR_NOSUCHNICK(server, nick, dest) server + " 401 " + nick + " " + dest + " : No such nick/channel\r\n"
# define ERR_CANNOTSENDTOCHAN(server, nick, dest) server + " 404 " + nick + " " + dest + " :Cannot send to channel\r\n"


# define ERR_NORECIPIENT(server, nick, command) server +  " 411 " + nick + " :No recipient given(" + command + ")\r\n"
# define ERR_NOTEXTTOSEND(server, nick) server +  " 412 " + nick + " :No text to send\r\n"

# define ERR_UNKNOWNCOMMAND(server, client, cmd) server + " 421 " + client +  " " + cmd + " :Unknown command\r\n"
# define ERR_NOTREGISTERED(server, cmd) server + " 451 " + cmd + " :You have not registered\r\n"
# define ERR_NEEDMOREPARAMS(server ,client, command) server + " 461 "+  client + " " + command + " :Not enough parameters\r\n"
# define ERR_ALREADYREGISTERED(server , client, command) server + " 462 " + client + " " + command + " :You may not reregister\r\n"
# define ERR_PASSWDMISMATCH(server, client) server + " 464 " + client + " :Password incorrect\r\n"

# define ERR_NONICKNAMEGIVEN(server ,client) server + " 431 " + client + " :No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(server, client, nick) server + " 432 " + client + " " + nick + " :Erroneus nickname\r\n"
# define ERR_NICKNAMEINUSE(server, client, nick) server + " 433 " client + " " + nick + " :Nickname is already in use\r\n"
# define ERR_NICKCOLLISION(client, nick, user, host) client + " " + nick + " ::Nickname collision KILL from " + user + "@" + host // wont be used

// channel
# define RPL_TOPIC(server, client, channel, topic)  server + " 332 " + client + " " + channel + " : " + topic 
# define RPL_NAMREPLY(server, client, channel, nick)  server + " 353 " + client +  " @ "+ channel +" :" + nick
# define RPL_ENDOFNAMES(server, client, channel)  server + " 366 " + client +  " "+ channel + " :End of /NAMES list."
# define ERR_BADCHANNELKEY(server, client, channel)  server + " 475 " + client +  " "+ channel + " :Cannot join channel (+k)"
# define ERR_INVITEONLYCHAN(server, client, channel)  server + " 473 " + client +  " "+ channel + " :Cannot join channel (+i)"
# define ERR_CHANNELISFULL(server, client, channel)  server + " 471 " + client +  " "+ channel + " :Cannot join channel (+l)"
# define ERR_NOSUCHCHANNEL(server, client, channel)  server + " 403 " + client +  " "+ channel + " :No such channel"
# define ERR_UMODEUNKNOWNFLAG(server, client)  server + " 501 " + client + " :Unknown MODE flag"
# define RPL_CHANNELMODEIS(server, client, channel,op, param)  ":" + server + " 324 " + client +  " " + channel +  " " + op  + param

// channel mode
# define ERR_CHANOPRIVSNEEDED(server, client, channel)  server + " 482 " + client +  " "+ channel + " : :You're not channel operator"
# define RPL_CREATIONTIME(server, client, channel, timee)  server + " 329 " + client +  " "+ channel + " " + timee
# define ERR_USERNOTINCHANNEL(server, client, nick , channel)  server + " 441 " + client + " " + nick + " " + channel + " :They aren't on that channel"
# define  ERR_NOTONCHANNEL(server, client , channel)   server + " 442 " + client  + " " + channel + " :You're not on that channel"

#endif