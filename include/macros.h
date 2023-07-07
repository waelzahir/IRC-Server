#ifndef MACROS_H
# define MACROS_H

# define USERLEN 12




# define I_MODE 1
# define T_MODE (1 << 1)
# define K_MODE (1 << 2)
# define O_MODE (1 << 3)
# define L_MODE (1 << 4)


# define ERR_NEEDMOREPARAMS(client, command) client + " " + command + " :Not enough parameters"
# define ERR_ALREADYREGISTERED(client) client + " :You may not reregister"
# define ERR_PASSWDMISMATCH(client) client + " :Password incorrect"

# define ERR_NONICKNAMEGIVEN(client) client + " :No nickname given"
# define ERR_ERRONEUSNICKNAME(client, nick) client + " " + nick + " :Erroneus nickname"
# define ERR_NICKNAMEINUSE(client, nick) client + " " + nick + " :Nickname is already in use"
# define ERR_NICKCOLLISION(client, nick, user, host) client + " " + nick + " ::Nickname collision KILL from " + user + "@" + host

#endif