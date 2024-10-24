#pragma once

#include "AMessage.hpp"
#include "NewException.hpp"
#include "Server.hpp"

class Invite : public AMessage
{
	public:
		/* exception class */
		class NeedMoreParamException : public NewException
		{
			public :
				virtual	~NeedMoreParamException() throw();
				virtual std::string	what() const throw();
		};
		class NotOnChannelException : public NewException
		{
			public :
				NotOnChannelException(const std::string &channel);
				virtual	~NotOnChannelException() throw();
				virtual std::string	what() const throw();
			private :
				NotOnChannelException();
				const std::string	mChannel;
		};
		class ChanOprivsNeededException : public NewException
		{
			public :
				ChanOprivsNeededException(const std::string &channel);
				virtual	~ChanOprivsNeededException() throw();
				virtual std::string	what() const throw();
			private :
				ChanOprivsNeededException();
				const std::string	mChannel;
		};
		class NoSuchNickException : public NewException
		{
			public :
				NoSuchNickException(const std::string &nick);
				virtual	~NoSuchNickException() throw();
				virtual std::string	what() const throw();
			private :
				NoSuchNickException();
				const std::string	mNick;
		};
		class UserOnChannelException : public NewException
		{
			public :
				UserOnChannelException(const std::string &user, const std::string &channel);
				virtual	~UserOnChannelException() throw();
				virtual std::string	what() const throw();
			private :
				UserOnChannelException();
				const std::string	mUser;
				const std::string	mChannel;
		};

		/* public member function */
		// constructor && destructor
		Invite(Client* origin, const std::string msg);
		virtual	~Invite();
		// cmd 실행
		virtual void	ExecuteCommand() throw(NewException);
		// 파라미터 초기화
		void		InitializeParameter() throw(NewException);
		std::string	GetInviteConfirmMsg();

	private:
		Invite();

		/* parameter of cmd */
		std::string	mNickname;
		std::string	mChannel;
};
