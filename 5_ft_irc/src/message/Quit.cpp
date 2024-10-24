#include <algorithm>

#include "Server.hpp"
#include "Quit.hpp"

Quit::Quit(Client* origin, const std::string msg) :
AMessage(origin, "QUIT", msg)
{
	if (mParamCount)
		mQuitMessage = mParamArray[0];
	else
		mQuitMessage = mOrigin->GetNickName();
}

void	Quit::ExecuteCommand()
{
	FillClientList();
	QuitBroadcast(mOrigin->GetClientPrefix() + "QUIT :Quit: " + mQuitMessage + "\r\n");
	Server::GetServer()->unregisterClientSocket(mOrigin->GetFd(), " closed.");
}

void	Quit::FillClientList()
{
	std::map<const std::string, Channel>			ChannelList = \
		Server::GetServer()->GetChannelList();
	std::map<const std::string, Channel>::iterator	it_ch = ChannelList.begin();

	for (; it_ch != ChannelList.end(); ++it_ch)
	{
		std::vector<const Client *>				vec_user = it_ch->second.GetUserList();
		std::vector<const Client *>::iterator	it_user = vec_user.begin();
		for (; it_user != vec_user.end(); ++it_user)
			AddClientList(*it_user);
		it_ch->second.RemoveOne(*mOrigin);
	}
}

void	Quit::AddClientList(const Client* client)
{
	std::vector<const Client *>::iterator	it_v = \
		std::find(mClientList.begin(), mClientList.end(), client);

	if (it_v == mClientList.end())
		mClientList.push_back(client);
}

void	Quit::QuitBroadcast(const std::string& msg)
{
	std::vector<const Client *>::iterator	it_v = mClientList.begin();
	Server*									server = Server::GetServer();

	for (; it_v != mClientList.end(); ++it_v)
		server->SendMessage(*(*it_v), msg);
}

Quit::~Quit()
{
}
