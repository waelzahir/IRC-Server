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
	char					mode;

	Channel();
	Channel(std::string);
	Channel(Channel const &);
	~Channel();

	void add_user(User &);
	void remove_user(User &);

	void set_mode(int flag);
	void unset_mode(int flag);
	bool get_mode_status(int flag);

	Channel&	operator=(Channel const &);
};

#endif /* * SPAN_H */
