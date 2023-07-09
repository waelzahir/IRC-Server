#ifndef IRCSYSTEM_HPP
# define IRCSYSTEM_HPP

# include <iostream>
# include <string>
# include <set>
# include <vector>
# include <algorithm>
# include <math.h>
# include <Server.hpp>
# include <User.hpp>
# include <algorithm>

class IrcSystem
{
private:
	Server *server;
public:
	std::vector<User> users;
	IrcSystem();
	IrcSystem(IrcSystem const &);
	~IrcSystem();
	void start_loop();
	void set_server(Server);
	void remove_server();
	void addUser(const User&);
	void removeUser(std::string );
	IrcSystem&	operator=(IrcSystem const &);
};

#endif /* * SPAN_H */
