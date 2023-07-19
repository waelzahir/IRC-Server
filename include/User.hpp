#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <string>
# include <set>
# include <vector>
# include <algorithm>
# include <math.h>
class User
{
public:
	int 		connected;
	int 		welcomed;
	int 		owner;
	std::string username;
	std::string nickname;
	std::string pass_auth;
	void	activateAuth();
	User();
	User(std::string, std::string);
	User(User const &);
	~User();

	User&	operator=(User const &);
	bool operator == (const User &);
	bool operator == (User &);
};

#endif /* * SPAN_H */
