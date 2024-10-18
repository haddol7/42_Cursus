#include <iostream>
#include "ft_irc.hpp"

int	main(int argc, char *argv[])
{
	Server *server;

	if (argc != 2)
	{
		std::cerr << "Invalid arguments" << std::endl;
		return (1);
	}
	server = Server::GetServer();
	server->InitServer(argv[1]);
	server->ExecServerLoop();

	delete server;
	return (0);
}
