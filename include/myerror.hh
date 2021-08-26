#ifndef MYERROR_HH
#define MYERROR_HH

#ifndef __cplusplus
#error C++ Required
#endif

#include <string>

class myerror {
public:
	std::string name = "", description = "";
	myerror(std::string name, std::string description)
		: name(name), description(description) {}
	myerror(std::string name)
		: name(name) {}
};

#endif // MYERROR_HH
