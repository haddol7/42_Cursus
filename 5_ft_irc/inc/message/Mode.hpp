#pragma once

#include <sstream>
#include "AMessage.hpp"
#include "Channel.hpp"

class Mode : public AMessage
{
	public:
		Mode(Client* origin, const std::string msg);
		virtual void		ExecuteCommand();
		bool				CheckParamAndGiveInfo();
		const std::string	GetModeString() const;
		bool				FindChannel();
		void				ExecuteAllLoop();
		bool				Execute_t(bool mode);
		bool				Execute_l(const std::string& num, bool mode);
		bool				Execute_k(const std::string& key, bool mode);
		bool				Execute_i(bool mode);
		bool				Execute_o(const std::string& client, bool mode);
		void				SendReply() const;
		virtual				~Mode();

	private:
		Mode();
		std::string			mModeList;
		std::string 		mTarget;
		Channel				*mChannel;
		std::stringstream	mReplyParam;
		std::stringstream	mReplyParamValues;
		int					mParamIter;
};
