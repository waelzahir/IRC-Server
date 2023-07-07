#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>
# include <string>
# include <set>
# include <vector>
# include <algorithm>
# include <math.h>
class Message
{
public:
	Message();
	Message(Message const &);
	~Message();

	Message&	operator=(Message const &);
};

#endif /* * SPAN_H */
