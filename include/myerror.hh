#ifndef MYERROR_HH
#define MYERROR_HH

#ifndef __cplusplus
#error C++ Required
#endif

#include <string>

class myerror {
public:
	std::string name, description;
	myerror(std::string name, std::string description)
	{
		this->name = name;
		this->description = description;
	}
	myerror(std::string name)
	{
		this->name = name;
		this->description = "";
	}
};

#endif // MYERROR_HH
