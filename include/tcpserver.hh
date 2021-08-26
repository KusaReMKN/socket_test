#ifndef TCP_SERVER_HH
#define TCP_SERVER_HH

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
#include "tcpclient.hh"

class tcp_accepted: public tcp_client {
	struct sockaddr_storage addr;
public:
	tcp_accepted(int sock, struct sockaddr_storage addr);
};

class tcp_server {
	int sockfd;
	int backlog = 5;
	std::size_t buflen = 1024;
public:
	tcp_server(std::string service);
	tcp_server(int sock);
	~tcp_server();
	tcp_accepted *waitconnect();
};

#endif /* TCP_SERVER_HH */
