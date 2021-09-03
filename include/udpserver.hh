#ifndef UDP_SERVER_HH
#define UDP_SERVER_HH

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

class udp_server {
	int sockfd;
	std::size_t buflen;
public:
	udp_server(std::string service);
	udp_server(int sock);
	~udp_server();
	void recv(std::string &data);
	void recv(std::string &data, struct sockaddr_storage &addr);
	void send(std::string data, struct sockaddr_storage addr);
};

#endif /* UDP_SERVER_HH */
