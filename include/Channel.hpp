#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <set>
# include <vector>
# include <algorithm>
# include <math.h>
# include "User.hpp"
class Channel
{

public:
	std::string				_name;
	std::vector<User>		_users;

	Channel();
	Channel(std::string);
	Channel(Channel const &);
	~Channel();

	void add_user(User &);
	void remove_user(User &);
	Channel&	operator=(Channel const &);
};

#endif /* * SPAN_H */
