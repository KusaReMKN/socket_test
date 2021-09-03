#include <iostream>
#include <string>
#include <cstdlib>

#include "myerror.hh"
#include "udpserver.hh"

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " port" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	try {
		udp_server* udp = new udp_server(argv[1]);
		struct sockaddr_storage addr;
		std::string buf;

		udp->recv(buf, addr);
		std::cout << "Client: " << buf << std::endl;
		udp->send(buf, addr);
		delete udp;
	} catch (myerror e) {
		std::cout << e.name << ": " << e.description << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::cout << "Success." << std::endl;

	return 0;
}
