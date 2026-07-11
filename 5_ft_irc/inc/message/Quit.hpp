#pragma once

#include <vector>

#include "AMessage.hpp"
#include "Client.hpp"

class Quit : public AMessage
{
	public:
		Quit(Client* origin, const std::string msg);
		virtual void	ExecuteCommand();
		virtual	~Quit();

	private:
		Quit();
		void	QuitBroadcast(const std::string& msg);
		void	FillClientList();
		void	AddClientList(const Client* client);

		std::string				mQuitMessage;
		std::vector<const Client *>	mClientList;
};
