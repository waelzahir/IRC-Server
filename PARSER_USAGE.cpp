#include <iostream>
#include "ReqParser.hpp"

int main()
{
    ReqParser parser("PRIVMSG user1, user2 cz :fsdfsd,xcv");
    while (parser.getStatus())
    {
        std::pair<int, std::string> tpair = parser.getToken();
        if (tpair.first == 1)
            parser.ListedParse(tpair);
        else 
            std::cout << tpair.first << " |"<< tpair.second << "|"<< std::endl;
    }
}