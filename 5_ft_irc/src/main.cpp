#include <iostream>
#include "ft_irc.hpp"

int	main(int argc, char *argv[])
{
	Server *server;

	if (argc != 3)
	{
		std::cerr << "Invalid arguments ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	server = Server::GetServer();
	if (server->InitServer(argv[1], argv[2]))
	{
		return (1);
	}
	server->ExecServerLoop();

	delete server;
	return (0);
}
