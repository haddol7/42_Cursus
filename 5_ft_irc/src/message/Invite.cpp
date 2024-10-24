#include "Invite.hpp"

/* exception class */
Invite::NeedMoreParamException::~NeedMoreParamException() throw() {}
std::string	Invite::NeedMoreParamException::what() const throw()
{
	return (ERR_NEEDMOREPARAMS("Invite"));
}

Invite::NotOnChannelException::NotOnChannelException(const std::string &channel) \
	: mChannel(channel) {}
Invite::NotOnChannelException::~NotOnChannelException() throw() {}
std::string	Invite::NotOnChannelException::what() const throw()
{
	return (ERR_NOTONCHANNEL(mChannel));
}

Invite::ChanOprivsNeededException::ChanOprivsNeededException(const std::string &channel) \
	: mChannel(channel) {}
Invite::ChanOprivsNeededException::~ChanOprivsNeededException() throw() {}
std::string	Invite::ChanOprivsNeededException::what() const throw()
{
	return (ERR_CHANOPRIVSNEEDED(mChannel));
}

Invite::NoSuchNickException::NoSuchNickException(const std::string &nick) \
	: mNick(nick) {}
Invite::NoSuchNickException::~NoSuchNickException() throw() {}
std::string	Invite::NoSuchNickException::what() const throw()
{
	return (ERR_NOSUCHNICK(mNick));
}

Invite::UserOnChannelException::UserOnChannelException(const std::string &user, const std::string &channel) \
	: mUser(user), mChannel(channel) {}

Invite::UserOnChannelException::~UserOnChannelException() throw() {}
std::string	Invite::UserOnChannelException::what() const throw()
{
	return (ERR_USERONCHANNEL(mUser, mChannel));
}

/* public member function */
// constructor && destructor
Invite::Invite(Client* origin, const std::string msg) : \
	AMessage(origin, "INVITE", msg) {}
Invite::~Invite(){}

// cmd 실행
void	Invite::ExecuteCommand() throw(NewException)
{	
	try
	{
		// 파라미터 초기화
		InitializeParameter();

		// 서버의 채널에 접근
		std::map<const std::string, Channel>	&channelList = \
			Server::GetServer()->GetChannelList();
		std::map<const std::string, Channel>::iterator	targetChannelIter = \
			channelList.find(mChannel);
		Channel	&targetChannel = targetChannelIter->second;

		// 초대하는 사람이 해당 채널에 없거나 해당 채널이 존재하지 않을 경우 ERR_NOTONCHANNEL
		if (targetChannelIter == channelList.end()
			|| !targetChannel.FindUserInChannelWithNick(mOrigin->GetNickName()))
			throw (Invite::NotOnChannelException(mChannel));
		// 채널이 invite_only 채널이고 초대하는 사람이 관리자 권한이 없을 때 ERR_CHANOPRIVSNEEDED
		if (!targetChannel.FindOpInChannelWithNick(mNickname) && \
			targetChannel.GetOneModeStatus(I_MODE))
			throw (Invite::ChanOprivsNeededException(mChannel));
		// 해당 채널에 초대하려는 사람이 이미 있을 때 ERR_USERONCHANNEL
		if (targetChannel.FindUserInChannelWithNick(mNickname))
			throw (Invite::UserOnChannelException(mNickname, mChannel));
		
		Client	*invitedOne = Server::GetServer()->ReturnClientOrNull(mNickname);
		targetChannel.InviteOne(invitedOne);
		ReplyToOrigin(RPL_INVITING(mChannel, mNickname));
		Server::GetServer()->SendMessage(*invitedOne, GetInviteConfirmMsg());
	}
	catch(const NewException &e)
	{
		std::cerr << e.what() << '\n';
		ReplyToOrigin(e.what());
	}
}

// 파라미터 초기화
void	Invite::InitializeParameter() throw(NewException)
{
	// 인자가 모자라면 ERR_NEEDMOREPARAMS
	if (mParamCount < 2)
		throw (Invite::NeedMoreParamException());
	
	mNickname = mParamArray[0];
	mChannel = mParamArray[1];

	// 해당 nick이 현재 서버에 없을 경우 ERR_NOSUCHNICK
	if (Server::GetServer()->ReturnClientOrNull(mNickname) == NULL)
		throw (Invite::NoSuchNickException(mNickname));
}

std::string	Invite::GetInviteConfirmMsg()
{
	return (":" + mOrigin->GetNickName() + "!" + \
		mOrigin->GetUserName() + "@" + mOrigin->GetHostName() + \
		" INVITE " + mNickname + " " + mChannel);
}
