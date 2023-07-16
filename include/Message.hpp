#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>
# include <string>
# include <set>
# include <vector>
# include <algorithm>
# include <math.h>
# include "Client.hpp"
class Message
{

public:
	Client		&_sender;
	std::string _source;
	std::string _tag;
	std::string _command;
	std::string _param;
	std::string _final_message;
	const std::string crlf = "\r\n";


	Message();
	Message(Client	&sender,const char * command);
	Message(Client	&sender,const char * command, std::string &source);
	Message(Message const &);

	void add_param(std::string &param);
	void set_param(std::string &param);
	void set_source(std::string &source);
	void set_command(std::string &command);
	void set_tag(std::string &tag);
	void set_message();
	void clear_final();
	size_t size();

	~Message();

	Message&	operator=(Message const &);
};

#endif /* * SPAN_H */
