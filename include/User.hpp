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
	std::string username;
	std::string nickname;
	User();
	User(std::string, std::string);
	User(User const &);
	~User();

	User&	operator=(User const &);
	bool operator == (const User &);
};

#endif /* * SPAN_H */
