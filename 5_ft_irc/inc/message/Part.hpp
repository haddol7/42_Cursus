#pragma once

#include "AMessage.hpp"

class Part : public AMessage
{
public:
	Part(Client* origin, const std::string msg);
	virtual void	ExecuteCommand();
	bool			IsValidChannel();
	bool			FindChannel();
	void			SendReply() const;
	virtual	~Part();

private:
	Part();
	std::string mTargetChannel;
	std::string mTargetMsg;
	std::string mOriginNick;
	Channel*	mChannel;
};
