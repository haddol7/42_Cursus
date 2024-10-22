#include "Join.hpp"

Join::Join(Client* origin, const std::string &msg) : \
	AMessage(origin, "Join", msg)
{
	parseParameter(getParameter());
}

Join::~Join()
{
}

void	Join::ExecuteCommand()
{
	std::map<const std::string, Channel>	&channelsInServer = \
		(Server::GetServer())->GetChannelList();

	while (!mChannelList.empty())
	{
		std::string	targetName = mChannelList.front();
		mChannelList.pop_front();

		std::map<const std::string, Channel>::iterator	target = \
			channelsInServer.find(targetName);
		
		// 채널이 없으면 새로 만든 후 최초로 join을 호출한 사람을 관리자로 삼는다.
		if (target == channelsInServer.end())
			channelsInServer[targetName] = Channel(targetName, *mOrigin);
		// 채널이 이미 존재할 경우
		else
		{
			try
			{
				// key 목록에 남은 키가 없다면 키 없이 채널에 가입을 시도한다.
				if (mChannelKeyList.empty())
					channelsInServer[targetName].AddUser(*mOrigin);
				// key 목록에 남은 키가 있다면 해당 키로 채널에 가입을 시도한다.
				else
				{
					channelsInServer[targetName].AddUserWithKey(*mOrigin, mChannelKeyList.front());
					mChannelKeyList.pop_front();
				}
			}
			// 채널 가입에 실패하였다면 에러 메세지를 서버에서 출력하고 클라이언트에게 보낸다.
			catch(const std::exception &e)
			{
				std::cerr << e.what() << std::endl;
				Server::GetServer()->SendMessage(*mOrigin, e.what());
			}
		}
	}
}

/* Join must not be called with default constructor(instance needs param) */
Join::Join() : \
	AMessage(NULL, "", std::string())
{}

/* private member function */
// parse parameter from msg
// prefix, command가 보장된 상태로 들어오므로 parameter만 파싱
const std::string	&Join::getParameter()
{
	if (mBuff[0] == ':')
		return (mBuff.substr(mBuff.find(" ", mBuff.find(" ") + 1) + 1));
	else
		return (mBuff.substr(mBuff.find(" ") + 1));
}

// # 또는 &으로 시작하는 parameter은 channel 목록(mChannelList)에 저장.
// 그렇지 않은 parameter 이후로는 모두 key 목록(mChannelKeyList)에 저장
void				Join::parseParameter(const std::string &parameter)
{
	std::istringstream	lineParser(parameter);
	std::string			nextParam;

	while (1)
	{
		std::getline(lineParser, nextParam, ' ');
		if (nextParam[0] == '#' && nextParam[0] == '&')
			mChannelList.push_back(nextParam);
		else
		{
			mChannelKeyList.push_back(nextParam);
			break ;
		}

		if (lineParser.eof())
			return ;
	}

	if (lineParser.eof())
		return ;

	while (1)
	{
		std::getline(lineParser, nextParam, ' ');
		mChannelKeyList.push_back(nextParam);

		if (lineParser.eof())
			return ;
	}
}
