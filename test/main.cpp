/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 05:13:05 by tel-mouh          #+#    #+#             */
/*   Updated: 2023/07/15 04:00:50 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
// #include <vector>
#include <queue>
#include <algorithm>
# include <iostream>
# include <sstream>
// using namespace std;
# include "../include/macros.h"


static std::stringstream& operator>> (std::stringstream& src, std::stringstream& dst)
{
	std::string temp;
    
    src >> temp;
    dst << temp;
    return dst;
}

static std::string extract_token(std::stringstream& src)
{
	std::string temp;

    if (src.eof())
        return std::string("");
    getline(src, temp, ',');
    return temp;
}

std::queue<std::pair <std::string, std::string> > get_channels_key(std::stringstream &stream)
{
	std::queue<std::pair <std::string, std::string> > map_ch;
    std::stringstream channles;
    std::stringstream keys;

    stream >> channles;
    stream >> keys;
    while (!channles.eof())
        map_ch.push(std::make_pair(extract_token(channles), extract_token(keys)));
    
	return map_ch;
}


int main(int argc, char const *argv[])
{


    std::string user = "#first,#two  key,key2";
    std::stringstream st;

    st << user;
    std::queue<std::pair <std::string, std::string> > map_ch;
    // use std::string; 
    // map_ch = get_channels_key(st);
    // std::cout << "size : "<<  map_ch.size() << std::endl;
    
    // map_ch.em();
    // std::cout << "size : "<<  map_ch.size() << std::endl;
    // std::cout << map_ch.front().first << std::endl;
    

    return 0;
		 
}

   