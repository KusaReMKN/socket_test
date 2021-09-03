#ifndef TCP_CLIENT_HH
#define TCP_CLIENT_HH

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

class tcp_client {
	int sockfd;
	std::size_t buflen;
public:
	tcp_client(std::string host, std::string service);
	tcp_client(int sock);
	~tcp_client();
	void send(std::string data);
	void recv(std::string &data);
};

#endif /* TCP_CLIENT_HH */
