/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 05:13:05 by tel-mouh          #+#    #+#             */
/*   Updated: 2023/07/08 18:10:40 by tel-mouh         ###   ########.fr       */
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
    // char mode = 0;
    // mode |= K_MODE;
    // mode &= ~K_MODE;
	// cout <<"hi: " << (int)mode << " hello" << endl;

    string user = "zebi";
    // use std::string; 


    string error = ERR_NONICKNAMEGIVEN(user);
    cout << error << endl;  
    return 0;
		 
}

   