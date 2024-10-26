#pragma once

#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Bot
{
    public:
        static std::vector<Bot> sBotList;
        static std::string      sBuffer;
        static std::vector<Bot>::iterator  GetBotChannel(std::string& channelName);
        static void                        AddBuffer(int sock, std::string buff);
        static void                        FinishBot(std::vector<Bot>::iterator it);
        static void                        ExitChannel(std::string& channelName);
        static int                         GetChannelCount();

        Bot(int sock, const std::string& channelName);

        int                 ProcessMessage(const std::string& msg);
        const std::string&  GetChannelName() const;
        int                 GetSockFd() const;

        ~Bot();
    private:
        Bot();
        void        startGame();
        void        checkAnswer(std::string& number);
        void        printResult(const std::string& number) const;
        void        generateRandomNumber();

        std::string mChannelName;
        int         mSock;
        int         mTryCount;
        int         mBallCount;
        int         mStrikeCount;
        std::string mRandomNumber;
};

static int                      InitBot(std::string IpAddress, std::string Port, std::string Password);
static void                     ExecBotLoop(int socket);
static void                     EventLoop(int epollFd, int sock);
static std::string              makeCommand();
static void                     ExecMessage(int socket, std::string msg);
static std::string              FindCommand(std::string& msg);
static bool                     CheckCommand();
static std::string::size_type   FindLastPosition(const std::string& msg);
static void                     Ping(int socket, std::string& msg);
static void                     Invite(int socket, std::string& msg);
static void                     Join(int sock, std::string& msg);
static void                     Part(std::string& msg);
static void                     Privmsg(std::string& msg);
static void                     Kick(std::string& msg);
static bool                     isTryDigit(std::string& number);