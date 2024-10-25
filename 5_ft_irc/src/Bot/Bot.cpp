#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cctype>
#include <cstring>

#include "Bot.hpp"

int main(int argc, char *argv[])
{
    std::string Buffer;
    int         socket;

    if (argc != 4)
    {
        std::cerr << "error: invalid arguments ./bot <IPaddress> <port> <password>" \
                  << std::endl;
        return (1);
    }
    socket = InitBot(argv[1], argv[2], argv[3]);
    ExecBotLoop(socket, Buffer);

    return (0);
}

static int InitBot(std::string IpAddress, std::string Port, std::string Password)
{
    struct sockaddr_in  serverAddr;

    int sock = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (sock == -1)
    {
        std::cerr << "Could not create socket" << std::endl;
        exit(1);
    }
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(Port.c_str()));
    inet_pton(AF_INET, IpAddress.c_str(), &serverAddr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) 
    {
        std::cerr << "Connection failed" << std::endl;
        exit(1);
    }

    std::string passCommand = "PASS " + Password + "\r\n";
    std::string nickCommand = "NICK Bot\r\n";
    std::string userCommand = "USER Bot 0 * :Bot\r\n";
    
    send(sock, passCommand.c_str(), passCommand.length(), 0);
    send(sock, nickCommand.c_str(), nickCommand.length(), 0);
    send(sock, userCommand.c_str(), userCommand.length(), 0);

    return (sock);
}

static void    ExecBotLoop(int sock, std::string& Buffer)
{
    char                buffer[2048];
    bool                registStatus = 0;
    std::vector<Bot>    BotList;

    while (true) 
    {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) {
            std::cerr << "Disconnected from server" << std::endl;
            break;
        }
        buffer[bytesReceived] = '\0';  // 널 종료
        AddBuffer(sock, Buffer, buffer, registStatus, BotList);
    }

    // 소켓 닫기
    close(sock);
}

static void    AddBuffer(int sock, std::string& Buffer, std::string buffer, bool& registStatus, std::vector<Bot>& BotList)
{
    Buffer = Buffer + buffer;

    while (CheckCommand(Buffer) == true)
    {
        ExecMessage(sock, makeCommand(Buffer), registStatus, BotList);
    }
}

static std::string makeCommand(std::string& Buffer)
{
    size_t		length;
	char		buff[513];

	length = Buffer.length();
	if (length >= 512)
	{
		Buffer.copy(buff, 512, 0);
		Buffer.erase(0, 512);
		buff[510] = '\r';
		buff[511] = '\n';
		buff[512] = '\0';
	}
	else
	{
		std::string::size_type	pos = Buffer.find("\r\n");
		Buffer.copy(buff, pos + 2, 0);
		Buffer.erase(0, pos + 2);
		buff[pos + 2] = '\0';
	}

	return (buff);
}

static void    ExecMessage(int sock, std::string msg, bool& registStatus, std::vector<Bot>& BotList)
{
    const char* commandList[] = {"001", "PING", "PRIVMSG", "INVITE", "JOIN", "PART", NULL};

    std::string command = FindCommand(msg);

    size_t	index = 0;
	for (; commandList[index] != NULL; ++index)
	{
		if (command == commandList[index])
			break ;
	}

    if (registStatus == false && index != 0)
        return ;

    switch (index)
    {
        case 0:
            registStatus = true;
            std::cout << "Bot connected to server!" << std::endl;
            break ;
        case 1:
            Ping(sock, msg);
            break ;
        case 2:
            Privmsg(msg, BotList);
            break ;
        case 3:
            Invite(sock, msg, BotList);
            break ;
        case 4:
            Join(sock, msg, BotList);
            break ;
        case 5:
            Part(msg, BotList);
            break ;
        default:
            break ;
    }
}

static bool CheckCommand(const std::string& Buffer)
{
    size_t	length;

	length = Buffer.length();
	if (length >= 512)
		return true;
	else if (Buffer.find("\r\n") != std::string::npos)
		return true;
	return false;
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
		end = msg.find("\r\n");

	std::string	cmd;
	if (pos != std::string::npos)
		cmd = msg.substr(pos, end - pos);

	return cmd;
}

static void Ping(int sock, std::string& msg)
{
    // PING/PONG 처리
    std::string::size_type  pos = msg.find("PING");
    std::string pongResponse = "PONG " + msg.substr(pos + 5); // PING 뒤의 주소
    send(sock, pongResponse.c_str(), pongResponse.length(), 0);
}

static void Invite(int sock, std::string& msg, std::vector<Bot>& BotList)
{
    std::string::size_type  pos = msg.find("Bot ", msg.find("INVITE"));
    std::string::size_type  last = msg.find("\r\n");
    
    if (pos + 4 >= last)
        return ;
    pos = msg.find_first_not_of(" ", pos + 4);
    std::string::size_type  end = msg.find(" ", pos);
    if (end == std::string::npos)
        end = last;

    std::string channelName = msg.substr(pos, end - pos);

    std::vector<Bot>::iterator  it = BotList.begin();

    for (;it != BotList.end(); ++it)
    {
        if (it->GetChannelName() == channelName)
        {
            std::string errorResponse = "PRIVMSG " + channelName + " :Bot is already in the channel\r\n";
            send(sock, errorResponse.c_str(), errorResponse.length(), 0);
            return ;
        }
    }

    std::string joinResponse = "JOIN " + channelName + "\r\n";
    send(sock, joinResponse.c_str(), joinResponse.length(), 0);
}

static void Join(int sock, std::string& msg, std::vector<Bot>& BotList)
{
    std::string::size_type  pos = msg.find("JOIN");
    std::string::size_type  last = msg.find("\r\n");

    if (pos + 5 >= last)
        return ;
    pos = msg.find_first_not_of(" ", pos + 5);
    std::string::size_type  end = msg.find(" ", pos);
    if (end == std::string::npos)
        end = last;

    std::string channelName = msg.substr(pos, end - pos);

    std::vector<Bot>::iterator  it = BotList.begin();

    for (; it != BotList.end(); ++it)
    {
        if (it->GetChannelName() == channelName)
            return ;
    }

    BotList.push_back(Bot(sock, channelName));
}

static void Part(std::string& msg, std::vector<Bot>& BotList)
{
    std::string::size_type  pos = msg.find("PART");
    std::string::size_type  last = msg.find("\r\n");

    if (pos + 5 >= last)
        return ;
    pos = msg.find_first_not_of(" ", pos + 5);
    std::string::size_type  end = msg.find(" ", pos);
    if (end == std::string::npos)
        end = last;

    std::string channelName = msg.substr(pos, end - pos);

    std::vector<Bot>::iterator  it = BotList.begin();

    for (; it != BotList.end(); ++it)
    {
        if (it->GetChannelName() == channelName)
        {
            BotList.erase(it);
            return ;
        }
    }
}

static void Privmsg(std::string& msg, std::vector<Bot>& BotList)
{
    std::string::size_type  pos = msg.find("PRIVMSG");
    std::string::size_type  last = msg.find("\r\n");

    if (pos + 5 >= last)
        return ;
    pos = msg.find_first_not_of(" ", pos + 5);
    std::string::size_type  end = msg.find(" ", pos);
    if (end == std::string::npos)
        end = last;

    std::string channelName = msg.substr(pos, end - pos);

    pos = msg.find(":", end);
    std::string message = msg.substr(pos, last - pos);

    std::vector<Bot>::iterator  it = BotList.begin();

    for (; it != BotList.end(); ++it)
    {
        if (it->GetChannelName() == channelName)
        {
            it->ProcessMessage(message);
            return ;
        }
    }
}

Bot::Bot(int sock, const std::string& channelName) :
mChannelName(channelName),
mSock(sock),
mTryCount(9),
mBallCount(0),
mStrikeCount(0)
{
    std::string BotMessage = "PRIVMSG " + mChannelName + " :Bot is now ready to play\r\n";
    send(mSock, BotMessage.c_str(), BotMessage.length(), 0);

    BotMessage = "PRIVMSG " + mChannelName + " :Type '!Bot start' to start game\r\n";
    send(mSock, BotMessage.c_str(), BotMessage.length(), 0);
}

void    Bot::ProcessMessage(const std::string& msg)
{
    std::string::size_type  pos = msg.find(":!Bot ");

    if (pos == std::string::npos || pos != 0)
        return ;

    pos = msg.find("start\r\n");
    if (pos != std::string::npos)
    {
        startGame();
        return ;
    }

    pos = msg.find_first_not_of(" ", 5);
    std::string::size_type  last = msg.find("\r\n");
    if (pos == last)
        return ;
    std::string number = msg.substr(pos, last - pos);
    checkAnswer(number);
}

const std::string&  Bot::GetChannelName() const
{
    return mChannelName;
}

void    Bot::startGame()
{
    mTryCount = 0;
    mBallCount = 0;
    mStrikeCount = 0;
    mRandomNumber = generateRandomNumber();

    std::string BotMessage = "PRIVMSG " + mChannelName + " :[GAME START]\r\n";
    send(mSock, BotMessage.c_str(), BotMessage.length(), 0);
}

std::vector<int> Bot::generateRandomNumber() 
{
    std::vector<int> digits;

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
    return randomNumber;
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
    if (number.length() != 4 || isTryDigit(number) == false)
    {
        std::string BotMessage = "PRIVMSG " + mChannelName + " :'" + number + "' is not in right form\r\n";
        send(mSock, BotMessage.c_str(), BotMessage.length(), 0);
    }
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (mRandomNumber[i] == number[j])
            {
                if (i == j)
                    ++mStrikeCount;
                else
                    ++mBallCount;
                break ;
            }
        }
    }
    ++mTryCount;
    if (mStrikeCount == 4)
    {
        std::string BotMessage = "PRIVMSG " + mChannelName + \
            " :[CORRECT!!!] " + (char)(mTryCount + '0') + " TRY\r\n";
        send(mSock, BotMessage.c_str(), BotMessage.length(), 0);
        return ;
    }
    std::string BotMessage = "PRIVMSG " + mChannelName + \
        " :" + (char)(mTryCount + '0') + ") [ " + (char)(mStrikeCount + '0') + \
        " Strike | " + (char)(mBallCount + '0') + " Ball ]\r\n";
    send(mSock, BotMessage.c_str(), BotMessage.length(), 0);
    if (mTryCount == 9)
    {
        std::string answer;
        for (int i = 0; i < 4; ++i)
            answer = answer + (char)(mRandomNumber[i] + '0');
        std::string BotMessage = "PRIVMSG " + mChannelName + \
            " :[FAILD] Answer : " + answer + "\r\n";
        send(mSock, BotMessage.c_str(), BotMessage.length(), 0);
    }
    else
    {
        std::string BotMessage = "PRIVMSG " + mChannelName + \
            " :" + (char)(9 - mTryCount + '0') + " TRY LEFT\r\n";
        send(mSock, BotMessage.c_str(), BotMessage.length(), 0);
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

Bot::~Bot()
{
}