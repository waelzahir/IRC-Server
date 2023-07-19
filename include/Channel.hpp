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
	char					mode;
	std::string				_key;
	std::vector<User>		_users;
	User					*_owner;

	Channel();
	Channel(std::string);
	Channel(Channel const &);
	~Channel();

	int add_user(User &, std::string&);
	void remove_user(User &);
	void remove_user(const User &);

	void set_mode(int flag);
	void unset_mode(int flag);
	bool get_mode_status(int flag);

	Channel&	operator=(Channel const &);
	bool operator == (const Channel &);
	bool operator == ( Channel &);
};

#endif /* * SPAN_H */
