#pragma once

#include "AMessage.hpp"

class Kick : public AMessage
{
public:
	Kick(Client* origin, const std::string msg);
	virtual void	ExecuteCommand();
	bool			IsValidChannel();
	bool			FindChannel();
	void			SendReply() const;
	virtual			~Kick();

private:
	Kick();
	std::string 		mTargetChannel;
	std::string 		mTargetClientStr;
	std::string 		mTargetReason;
	std::string 		mOriginNick;
	Channel*			mChannel;
	const Client*		mTargetClientPtr;
};
