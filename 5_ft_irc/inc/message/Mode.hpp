#pragma once

#include <sstream>
#include "AMessage.hpp"
#include "Channel.hpp"

// 		i, t, k, o, l	ERR_NEEDMOREPARAMS	
// 467	k				ERR_KEYSET				"<channel> :Channel key already set”
// 482	i, t, k, o, l	ERR_CHANOPRIVSNEEDED	"<channel> :You're not channel operator”
// 441	o				ERR_USERNOTINCHANNEL	"<nick> <channel> :They aren't on that channel”
// 472	invalid			ERR_UNKNOWNMODE			"<char> :is unknown mode char to me for <channel>”
// 324	none			RPL_CHANNELMODEIS		"<channel> <mode> <mode params>”

class Mode : public AMessage
{
	public:
		Mode(Client* origin, const std::string msg);
		bool			FindChannel();
		void			SendReply() const;
		virtual void	ExecuteCommand();
		void			ExecuteAllLoop();
		bool			Execute_t(bool mode);
		bool			Execute_l(const std::string& num, bool mode);
		bool			Execute_k(const std::string& key, bool mode);
		bool			Execute_i(bool mode);
		bool			Execute_o(const std::string& client, bool mode);
		virtual			~Mode();

	private:
		Mode();
		std::string			mModeList;
		std::string 		mTarget;
		Channel				*mChannel;
		std::stringstream	mReplyParam;
		std::stringstream	mReplyParamValues;
		int					mParamIter;
};
