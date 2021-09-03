#include <iostream>
#include <string>
#include <cstdlib>

#include "myerror.hh"
#include "tcpclient.hh"

int main(int argc, char **argv)
{
	if (argc != 3) {
		std::cout << "Usage: " << argv[0] << " host port" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	try {
		tcp_client* tcp = new tcp_client(argv[1], argv[2]);
		std::string buf;

		std::cin >> buf;
		tcp->send(buf + "\r\n");
		tcp->recv(buf);
		std::cout << "Server: " << buf << std::endl;
		delete tcp;
	} catch (myerror e) {
		std::cout << e.name << ": " << e.description << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::cout << "Success." << std::endl;

	return 0;
}
