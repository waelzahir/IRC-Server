/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReqParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:15:14 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/09 23:03:21 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQPARSER_HPP
#define REQPARSER_HPP
#include <vector>
#include <iostream>

enum {
    ALONE,
    MULTI,
    MULTISPLI
};
 
class ReqParser
{
    public:
        ReqParser(std::stringstream &stream);
        int getStatus(); // gets the status of the parser  : "if there is more tokens to get"
        void    ListedParse(std::pair<int, std::string> to); // parse the 'MULTI' flagged token, used only if neccesary
        std::pair<int, std::string> getToken();
        
    private:
        void    ParseSubToken(std::string command, std::string& token);
        std::vector <std::pair<int, std::string> >  tokens; // the first element is the type of the token, he second is the token;
};
#endif