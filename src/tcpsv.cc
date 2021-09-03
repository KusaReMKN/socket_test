#include <iostream>
#include <string>
#include <cstdlib>

#include "myerror.hh"
#include "tcpserver.hh"

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " port" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	try {
		tcp_server* svr = new tcp_server(argv[1]);
		tcp_accepted* tcp = svr->waitconnect();
		std::string buf;

		tcp->recv(buf);
		std::cout << "Client: " << buf << std::endl;
		tcp->send(buf);
		delete tcp;
		delete svr;
	} catch (myerror e) {
		std::cout << e.name << ": " << e.description << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::cout << "Success." << std::endl;

	return 0;
}
