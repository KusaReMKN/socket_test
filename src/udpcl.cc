#include <iostream>
#include <string>
#include <cstdlib>

#include "myerror.hh"
#include "udpclient.hh"

int main(int argc, char **argv)
{
	if (argc != 3) {
		std::cout << "Usage: " << argv[0] << " host port" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	try {
		udp_client* udp = new udp_client(argv[1], argv[2]);
		std::string buf;

		std::cin >> buf;
		udp->send(buf + "\r\n");
		udp->recv(buf);
		std::cout << "Server: " << buf << std::endl;
		delete udp;
	} catch (myerror e) {
		std::cout << e.name << ": " << e.description << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::cout << "Success." << std::endl;

	return 0;
}
