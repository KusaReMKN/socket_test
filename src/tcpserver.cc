#include "tcpserver.hh"

tcp_accepted::tcp_accepted(int sock, struct sockaddr_storage addr):
	tcp_client(sock), addr(addr) {}

tcp_server::tcp_server(std::string service):
	backlog(5), buflen(1024)
{
	int err;
	struct addrinfo hints, *result, *rp;

	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	err = getaddrinfo(NULL, service.c_str(), &hints, &result);
	if (err != 0)
		throw myerror("tcp_server:getaddrinfo", gai_strerror(err));

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		int sock;

		sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sock == -1)
			continue;
		if (bind(sock, rp->ai_addr, rp->ai_addrlen) != 0) {
			close(sock);
			continue;
		}
		if (listen(sock, this->backlog) == 0) {
			this->sockfd = sock;
			break;
		}
		close(sock);
	}
	freeaddrinfo(result);
	if (rp == NULL)
		throw myerror("tcp_server", "Could not listen");
}

tcp_server::tcp_server(int sock): sockfd(sock), backlog(5), buflen(1024) {}

tcp_server::~tcp_server()
{
	close(this->sockfd);
}

tcp_accepted *tcp_server::waitconnect()
{
	int sock;
	struct sockaddr_storage addr;
	socklen_t addrlen = sizeof(addr);

	sock = accept(sockfd, (struct sockaddr *)&addr, &addrlen);
	if (sock == -1)
		throw myerror("tcp_server:accept", std::strerror(errno));
	return new tcp_accepted(sock, addr);
}
