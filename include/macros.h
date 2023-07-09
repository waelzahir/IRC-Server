#ifndef MACROS_H
# define MACROS_H

# define USERLEN 12


# define I_MODE 1
# define T_MODE (1 << 1)
# define K_MODE (1 << 2)
# define O_MODE (1 << 3)
# define L_MODE (1 << 4)

# define ERR_UNKNOWNCOMMAND(server, client, cmd) server + " 421 " + client +  " " + cmd + " :Unknown command\r\n"
# define ERR_NOTREGISTERED(server, cmd) server + " 451 " + cmd + " :You have not registered\r\n"
# define ERR_NEEDMOREPARAMS(server ,client, command) server + " 461 "+  client + "PASS" + " :Not enough parameters\r\n"
# define ERR_ALREADYREGISTERED(server , client) server + " 462 " + client + " PASS"+ " :You may not reregister\r\n"
# define ERR_PASSWDMISMATCH(server, client) server + " 464 " + client + " :Password incorrect\r\n"

# define ERR_NONICKNAMEGIVEN(server ,client) server + " 431 " + client + " :No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(server, client, nick) server+ " 432 " + client + " " + nick + " :Erroneus nickname\r\n"
# define ERR_NICKNAMEINUSE(server, client, nick) server + " 433 " client + " " + nick + " :Nickname is already in use\r\n"
# define ERR_NICKCOLLISION(client, nick, user, host) client + " " + nick + " ::Nickname collision KILL from " + user + "@" + host // wont be used

#endif