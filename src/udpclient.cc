#include "udpclient.hh"

udp_client::udp_client(std::string host, std::string service)
{
	int err;
	struct addrinfo hints, *result, *rp;

	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	err = getaddrinfo(host.c_str(), service.c_str(), &hints, &result);
	if (err != 0)
		throw myerror("udp_client:getaddrinfo", gai_strerror(err));

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		int sock;

		sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sock == -1)
			continue;
		if (connect(sock, rp->ai_addr, rp->ai_addrlen) != -1) {
			sockfd = sock;
			break;
		}
		close(sock);
	}
	freeaddrinfo(result);
	if (rp == NULL)
		throw myerror("udp_client", "Could not connect");
}

udp_client::udp_client(int sock): sockfd(sock) {}

udp_client::~udp_client()
{
	close(sockfd);
}

void udp_client::send(std::string data)
{
	if (write(sockfd, data.c_str(), data.length()) < 0)
		throw myerror("send:write", std::strerror(errno));
}

void udp_client::recv(std::string &data)
{
	std::vector<char> buf(buflen);
	if (read(sockfd, buf.data(), buf.size()) < 0)
		throw myerror("recv:read", std::strerror(errno));
	data = buf.data();
}
