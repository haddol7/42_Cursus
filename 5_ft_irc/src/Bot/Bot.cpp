#include <iostream>
#include <vector>
#include <sstream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cctype>
#include <cstring>
#include <errno.h>

#include "Bot.hpp"

std::vector<Bot> Bot::sBotList;
std::string      Bot::sBuffer;

int main(int argc, char *argv[])
{
    int         socket;

    if (argc != 4)
    {
        std::cerr << "error: invalid arguments ./bot <IPaddress> <port> <password>\n";
        return (1);
    }
    socket = InitBot(argv[1], argv[2], argv[3]);
    ExecBotLoop(socket);

    return (0);
}

static int InitBot(std::string IpAddress, std::string Port, std::string Password)
{
    struct sockaddr_in  serverAddr;

    int sock = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (sock == -1)
    {
        std::cerr << "Could not create socket\n";
        exit(1);
    }
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(Port.c_str()));
    inet_pton(AF_INET, IpAddress.c_str(), &serverAddr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0 && errno != EINPROGRESS) 
    {
        std::cerr << "Connection failed\n";
        close(sock);
        exit(1);
    }

    std::string passCommand = "PASS " + Password + "\r\n";
    std::string nickCommand = "NICK Bot\r\n";
    std::string userCommand = "USER Bot root * :Bot\r\n";
    
    send(sock, passCommand.c_str(), passCommand.length(), 0);
    send(sock, nickCommand.c_str(), nickCommand.length(), 0);
    send(sock, userCommand.c_str(), userCommand.length(), 0);

    return (sock);
}

static void    ExecBotLoop(int sock)
{
    // epoll 인스턴스 생성
    int epollFd = epoll_create1(0);
    if (epollFd < 0) 
    {
        std::cerr << "Epoll creation failed: " << strerror(errno) << "\n";
        close(sock);
        exit(1);
    }

    // epoll 이벤트 설정
    struct epoll_event event;
    event.events = EPOLLIN; // 읽기와 쓰기 이벤트 감지
    event.data.fd = sock;

    // epoll에 소켓 추가
    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, sock, &event) < 0) 
    {
        std::cerr << "Epoll ctl failed: " << strerror(errno) << "\n";
        close(sock);
        close(epollFd);
        exit(1);
    }

    // 이벤트 루프
    EventLoop(epollFd, sock);

    // 소켓 닫기
    close(sock);
}

static void EventLoop(int epollFd, int sock)
{
    while (true) 
    {
        struct epoll_event events[1];
        int nfds = epoll_wait(epollFd, events, 1, -1); // 블록킹 모드

        if (nfds < 0) 
        {
            std::cerr << "Epoll wait error: " << strerror(errno) << "\n";
            break;
        }

        for (int i = 0; i < nfds; ++i) 
        {
            char buffer[1024];
            int bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived <= 0) 
            {
                std::cerr << "Connection closed or error occurred\n";
                close(sock);
                break;
            }
            buffer[bytesReceived] = '\0';
            Bot::AddBuffer(sock, buffer);
        }
    }
}

void    Bot::AddBuffer(int sock, std::string buffer)
{
    Bot::sBuffer = Bot::sBuffer + buffer; // addBuffer static 함수 만들기 

    while (CheckCommand() == true)
    {
        ExecMessage(sock, makeCommand());
    }
}

static bool CheckCommand()
{
    size_t	length;

	length = Bot::sBuffer.length();
	if (length >= 512)
		return true;
    else if (Bot::sBuffer.find("\r\n") != std::string::npos)
		return true;
    else
	    return false;
}

static std::string makeCommand()
{
	char		buff[513];

	std::string::size_type	pos = Bot::sBuffer.find("\r\n");
	if (pos >= 511)
	{
		Bot::sBuffer.copy(buff, 512, 0);
		Bot::sBuffer.erase(0, 512);
		buff[510] = '\r';
		buff[511] = '\n';
		buff[512] = '\0';
	}
	else
	{
        pos = pos + 2;
		Bot::sBuffer.copy(buff, pos, 0);
		Bot::sBuffer.erase(0, pos);
		buff[pos] = '\0';
	}
	return (buff);
}

static void    ExecMessage(int sock, std::string msg)
{
    const char* commandList[] = {"001", "PING", "PRIVMSG", "INVITE", "JOIN", "PART", "KICK", NULL};

    std::string command = FindCommand(msg);

    size_t	index = 0;
	for (; commandList[index] != NULL; ++index)
	{
		if (command == commandList[index])
			break ;
	}

    switch (index)
    {
        case 0:
            std::cerr << "Bot connected to server!" << std::endl;
            break ;
        case 1:
            Ping(sock, msg);
            break ;
        case 2:
            Privmsg(msg);
            break ;
        case 3:
            Invite(sock, msg);
            break ;
        case 4:
            Join(sock, msg);
            break ;
        case 5:
            Part(msg);
            break ;
        case 6:
            Kick(msg);
            break ;
        default:
            break ;
    }
}

static std::string  FindCommand(std::string& msg)
{
    std::string::size_type	pos;
	std::string::size_type	end;

	if (msg[0] == ':')
	{
		pos = msg.find(' ');
		if (pos != std::string::npos)
			++pos;
	}
	else
		pos = 0;
	end = msg.find(' ', pos);

    if (end == std::string::npos)
    {
        end = msg.find("\r\n");
    }

    std::string	cmd;
	if (pos != std::string::npos)
		cmd = msg.substr(pos, end - pos);

    return cmd;
}

static void Ping(int sock, std::string& msg)
{
    // PING/PONG 처리
    const std::string   COMMAND = "PING";

    std::string::size_type  pos = msg.find(COMMAND);
    std::string pongResponse = "PONG" + msg.substr(pos + COMMAND.length()); // PING 뒤의 주소
    send(sock, pongResponse.c_str(), pongResponse.length(), 0);
}

static void Invite(int sock, std::string& msg)
{
    const std::string   COMMAND = "INVITE";

    std::string::size_type  pos = msg.find("Bot ", msg.find("INVITE"));
    std::string::size_type  last = msg.find("\r\n");
    
    if (pos == std::string::npos)
        return ;
    pos = msg.find(" ", pos);
    if (pos == std::string::npos)
        return ;
    pos = msg.find_first_not_of(" ", pos);
    if (pos == last)
        return ;
    if (msg[pos] == ':')
        ++pos;

    std::string::size_type  end = msg.find(" ", pos);
    if (end == std::string::npos)
        end = last;

    if (end - pos <= 0)
        return ;
    std::string channelName = msg.substr(pos, end - pos);

    std::vector<Bot>::iterator  it = Bot::GetBotChannel(channelName);
    if (it == Bot::sBotList.end())
    {
        std::string joinResponse = "JOIN " + channelName + "\r\n";
        send(sock, joinResponse.c_str(), joinResponse.length(), 0);
    }
    else
    {
        std::string errorResponse = "PRIVMSG " + channelName + " :Bot is already in the channel\r\n";
        send(sock, errorResponse.c_str(), errorResponse.length(), 0);
    }
}

static void Join(int sock, std::string& msg)
{
    const std::string   COMMAND = "JOIN";

    std::string::size_type  pos = msg.find(COMMAND);
    std::string::size_type  last = msg.find("\r\n");

    pos = msg.find_first_not_of(" ", pos + COMMAND.length());
    if (pos == last)
        return ;
    if (msg[pos] == ':')
        ++pos;

    std::string::size_type  end = msg.find(" ", pos);
    if (end == std::string::npos)
        end = last;

    if (end - pos <= 0)
        return ;
    std::string channelName = msg.substr(pos, end - pos);

    if (Bot::GetBotChannel(channelName) == Bot::sBotList.end())
    {
        Bot::sBotList.push_back(Bot(sock, channelName));
        std::cerr << "Bot joined channel [ " << channelName \
                  << " ]\nTotal : " << Bot::GetChannelCount() << "\n";
    }
}

static void Part(std::string& msg)
{
    const std::string   COMMAND = "PART";

    std::string::size_type  pos = msg.find(COMMAND);
    std::string::size_type  last = msg.find("\r\n");

    if (pos + COMMAND.length() >= last)
        return ;
    pos = msg.find_first_not_of(" ", pos + COMMAND.length());
    std::string::size_type  end = msg.find(" ", pos);
    if (end == std::string::npos)
        end = last;

    std::string channelName = msg.substr(pos, end - pos);
    Bot::ExitChannel(channelName);
}

static void Privmsg(std::string& msg)
{
    const std::string COMMAND = "PRIVMSG";

    std::string::size_type  pos = msg.find(COMMAND);
    std::string::size_type  last = msg.find("\r\n");

    if (pos + COMMAND.length() >= last)
        return ;
    pos = msg.find_first_not_of(" ", pos + COMMAND.length());
    std::string::size_type  end = msg.find(" ", pos);
    if (end == std::string::npos)
        end = last;

    std::string channelName = msg.substr(pos, end - pos);

    pos = msg.find(":", end);
    std::string message = msg.substr(pos, last - pos);

    std::vector<Bot>::iterator  it = Bot::GetBotChannel(channelName);
    if (it != Bot::sBotList.end())
    {
        if (it->ProcessMessage(message))
            Bot::FinishBot(it);
    }
}

static void Kick(std::string& msg)
{
    const std::string   COMMAND = "KICK";

    std::string::size_type  pos = msg.find(COMMAND);
    std::string::size_type  last = msg.find("\r\n");
    if (pos + COMMAND.length() >= last)
        return ;

    pos = msg.find_first_not_of(" ", pos + COMMAND.length());
    std::string::size_type  end = msg.find(" ", pos);
    if (end == std::string::npos)
        return ;
    std::string channelName = msg.substr(pos, end - pos);

    pos = msg.find_first_not_of(" ", end);
    end = msg.find(" ", pos);
    if (end == std::string::npos)
        end = last;
    std::string targetName = msg.substr(pos, end - pos);

    if (targetName == "Bot")
        Bot::ExitChannel(channelName);
}

int Bot::GetChannelCount()
{
    int                         count = 0;
    std::vector<Bot>::iterator  it = Bot::sBotList.begin();

    for (; it != Bot::sBotList.end(); ++it)
        ++count;
    return count;
}

void    Bot::ExitChannel(std::string& channelName)
{
    std::vector<Bot>::iterator  it = Bot::GetBotChannel(channelName);
    if (it != Bot::sBotList.end())
    {
        Bot::sBotList.erase(it);
        std::cerr << "Bot exited channel [ " << channelName \
                  << " ]\nTotal : " << Bot::GetChannelCount() << "\n";
    }
}

void    Bot::FinishBot(std::vector<Bot>::iterator it)
{
    int         sock = it->GetSockFd();
    std::string Message = "PART " + it->GetChannelName() + " :Bot finished\r\n";

    send(sock, Message.c_str(), Message.length(), 0);
}

Bot::Bot(int sock, const std::string& channelName) :
mChannelName(channelName),
mSock(sock),
mTryCount(9),
mBallCount(0),
mStrikeCount(0)
{
    std::string Message = "PRIVMSG " + mChannelName \
                          + " :Bot is now ready to play\r\nPRIVMSG " \
                          + mChannelName + " :Type '!Bot start' to start game\r\n";
    send(mSock, Message.c_str(), Message.length(), 0);
}

int    Bot::ProcessMessage(const std::string& msg)
{
    const std::string   COMMAND = ":!Bot ";
    std::string::size_type  pos = msg.find(COMMAND);

    if (pos == std::string::npos || pos != 0)
        return 0;

    pos = msg.find_first_not_of(" ", COMMAND.length());
    std::string::size_type  last = msg.find("\r\n");;
    if (pos == last)
        return 0;
    std::string arg = msg.substr(pos, last - pos);

    if (arg == "start")
        startGame();
    else if (arg == "finish")
        return 1;
    else
        checkAnswer(arg);
    return 0;
}

const std::string&  Bot::GetChannelName() const
{
    return mChannelName;
}

int Bot::GetSockFd() const
{
    return mSock;
}

void    Bot::startGame()
{
    mTryCount = 0;
    mBallCount = 0;
    mStrikeCount = 0;
    generateRandomNumber();

    std::string BotMessage = "PRIVMSG " + mChannelName + " :[GAME START]\r\n";
    send(mSock, BotMessage.c_str(), BotMessage.length(), 0);
}

void Bot::generateRandomNumber() 
{
    std::vector<int> digits;

    mRandomNumber.clear();

    // 0-9까지의 숫자를 벡터에 추가
    for (int i = 0; i <= 9; ++i) {
        digits.push_back(i);
    }

    // 랜덤 시드 초기화
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    // 벡터를 랜덤으로 섞음
    std::random_shuffle(digits.begin(), digits.end());

    // 첫 4자리 숫자 선택 (중복 없이)
    std::vector<int> randomNumber(digits.begin(), digits.begin() + 4);
    for (int i = 0; i < 4; ++i)
        mRandomNumber = mRandomNumber + (char)(randomNumber[i] +'0');
}

void    Bot::checkAnswer(std::string& number)
{
    if (mTryCount == 9)
    {
        std::string BotMessage = "PRIVMSG " + mChannelName + \
            " :Please restart the game\r\n";
        send(mSock, BotMessage.c_str(), BotMessage.length(), 0);
        return ;
    }
    else if (number.length() != 4 || isTryDigit(number) == false)
    {
        std::string BotMessage = "PRIVMSG " + mChannelName + " :'" + number + "' is not in right form\r\n";
        send(mSock, BotMessage.c_str(), BotMessage.length(), 0);
        return ;
    }
    mStrikeCount = 0;
    mBallCount = 0;
    for (std::string::size_type i = 0; i < 4; ++i)
    {
        std::string::size_type  pos = mRandomNumber.find(number[i]);
        if (pos == i)
            ++mStrikeCount;
        else if (pos != std::string::npos)
            ++mBallCount;
    }
    ++mTryCount;

    printResult(number);
}

void    Bot::printResult(const std::string& number) const
{
    std::stringstream   stream;
    std::string         Message;

    if (mStrikeCount == 4)
    {
        stream << "PRIVMSG " << mChannelName << " :[CORRECT!!!] " \
               << mTryCount << " TRY\r\n";
        Message = stream.str();
        send(mSock, Message.c_str(), Message.length(), 0);
        return ;
    }
    stream << "PRIVMSG " << mChannelName << " :" << mTryCount \
           << ") " << number << " [ " << mStrikeCount \
           << " Strike | " << mBallCount << " Ball ]\r\n";
    Message = stream.str();
    send(mSock, Message.c_str(), Message.length(), 0);
    if (mTryCount == 9)
    {
        Message = "PRIVMSG " + mChannelName + " :[FAILD] Answer : " \
                + mRandomNumber + "\r\n";
        send(mSock, Message.c_str(), Message.length(), 0);
    }
    else
    {
        stream.str("");
        stream << "PRIVMSG " << mChannelName << " :" \
               << 9 - mTryCount << " TRY LEFT\r\n";
        Message = stream.str();
        send(mSock, Message.c_str(), Message.length(), 0);
    }
}

static bool isTryDigit(std::string& number)
{
    for (int i = 0; i < 4; ++i)
    {
        if (isdigit(number[i]) == false)
            return false;
    }
    return true;
}

std::vector<Bot>::iterator  Bot::GetBotChannel(std::string& channelName)
{
    std::vector<Bot>::iterator  it = Bot::sBotList.begin();

    for (; it != Bot::sBotList.end(); ++it)
    {
        if (it->GetChannelName() == channelName)
            return it;
    }
    return it;
}

Bot::~Bot()
{
}