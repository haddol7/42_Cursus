#pragma once

#include "AMessage.hpp"

class Topic : public AMessage
{
public:
	Topic(Client* origin, const std::string msg);
	virtual void	ExecuteCommand();
	bool			Isvalidchannel();
	bool			IsOperatorOrReplyInfo();
	void			SetTopic();
	void			SendReply() const;
	bool			FindChannel();
	virtual			~Topic();

private:
	Topic();
	std::string	mTargetChannel;
	std::string	mTargetTopic;
	std::string	mOriginNick;
	Channel		*mChannel;

};
