#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>
# include <string>
# include <set>
# include <vector>
# include <algorithm>
# include <math.h>
class Commands
{
public:
	Commands();
	Commands(Commands const &);
	~Commands();
	void pass(std::string, std::string _args);

	Commands&	operator=(Commands const &);
};

#endif /* * SPAN_H */
