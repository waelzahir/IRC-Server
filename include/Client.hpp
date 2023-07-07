#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>
# include <set>
# include <vector>
# include <algorithm>
# include <math.h>
# include "Channel.hpp"
# include "User.hpp"
class Client
{
public:
	int fd;
	User _client_user;

	Client();
	Client(Client const &);
	~Client();

	void set_client_user(User &);
	void join_channel(Channel &);
	void leave_channel(Channel &);
	Client&	operator=(Client const &);
};

#endif /* * SPAN_H */
