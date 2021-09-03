#ifndef UDP_CLIENT_HH
#define UDP_CLIENT_HH

#ifndef __cplusplus
#error C++ Required.
#endif /* __cplusplus */

#include <string>
#include <vector>

#include <cerrno>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "myerror.hh"

class udp_client {
	int sockfd;
	std::size_t buflen;
public:
	udp_client(std::string host, std::string service);
	udp_client(int sock);
	~udp_client();
	void send(std::string data);
	void recv(std::string &data);
};

#endif /* UDP_CLIENT_HH */
