/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 05:13:05 by tel-mouh          #+#    #+#             */
/*   Updated: 2023/07/06 20:26:41 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
# include <iostream>
using namespace std;
# include "../include/macros.h"

int main(int argc, char const *argv[])
{
	std::string clientName = "John";
	std::string command = "";
    std::string errorMessage = ERR_NEEDMOREPARAMS(clientName, command);
    std::cout << errorMessage << std::endl;
    return 0;
		
}
