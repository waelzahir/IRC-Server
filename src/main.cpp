/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:05:11 by tel-mouh          #+#    #+#             */
/*   Updated: 2023/07/26 23:38:23 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcSystem.hpp"

int main(int ac, char	**av)
{
	if (ac != 3)
	{
		std::cout << "./ircserv <port> <password> " << std::endl;
		return 0;
	}
	IrcSystem irc;
	try
	{
		irc.set_server(Server(av[2], av[1]));
	}
	catch(std::string& e)
	{
		std::cerr << e << std::endl;
		return 0;
	}
	
	irc.start_loop();
	return 0;
}
