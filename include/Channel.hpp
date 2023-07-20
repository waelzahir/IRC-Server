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
	std::set<std::string>	inveted;
	User					*_owner;
	int						_user_limit;

	Channel();
	Channel(std::string);
	Channel(Channel const &);
	~Channel();

	int add_user(User &, std::string&);
	int remove_user(User &);
	int remove_user(const User &);
	User* get_user(std::string &name_user);
	User* get_user(const User& user);
	User* get_user(User& user);

	void set_mode(int flag);
	void unset_mode(int flag);
	bool get_mode_status(int flag);

	std::string get_channels_users();

	Channel&	operator=(Channel const &);
	bool operator == (const Channel &);
	bool operator == ( Channel &);
};

#endif /* * SPAN_H */
