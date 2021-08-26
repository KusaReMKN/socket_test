#include "udpserver.hh"

udp_server::udp_server(std::string service)
{
	int err;
	struct addrinfo hints, *result, *rp;

	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	err = getaddrinfo(NULL, service.c_str(), &hints, &result);
	if (err != 0)
		throw myerror("udp_server:getaddrinfo", gai_strerror(err));

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		int sock;

		sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sock == -1)
			continue;
		if (bind(sock, rp->ai_addr, rp->ai_addrlen) == 0) {
			this->sockfd = sock;
			break;
		}
		close(sock);
	}
	freeaddrinfo(result);
	if (rp == NULL)
		throw myerror("udp_server", "Could not listen");
}

udp_server::udp_server(int sock): sockfd(sock) {}

udp_server::~udp_server()
{
	close(this->sockfd);
}

void udp_server::recv(std::string &data)
{
	std::vector<char> buf(buflen);
	if (read(sockfd, buf.data(), buf.size()) < 0)
		throw myerror("recv:read", std::strerror(errno));
	data = buf.data();
}

void udp_server::recv(std::string &data, struct sockaddr_storage &addr)
{
	socklen_t len = sizeof(addr);
	std::vector<char> buf(buflen);
	if (recvfrom(sockfd, buf.data(), buf.size(), 0,
				(struct sockaddr *)&addr, &len) < 0)
		throw myerror("recv:read", std::strerror(errno));
	data = buf.data();
}

void udp_server::send(std::string data, struct sockaddr_storage addr)
{
	if (sendto(sockfd, data.c_str(), data.length(), 0,
				(struct sockaddr *)&addr, sizeof(addr)) < 0)
		throw myerror("send:write", std::strerror(errno));
}
