#pragma once

#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Bot
{
    public:
        Bot(int sock, const std::string& channelName);

        void                ProcessMessage(const std::string& msg);
        const std::string&  GetChannelName() const;

        ~Bot();
    private:
        Bot();
        void                startGame();
        void                checkAnswer(std::string& number);
        std::vector<int>    generateRandomNumber();

        std::string         mChannelName;
        int                 mSock;
        int                 mTryCount;
        int                 mBallCount;
        int                 mStrikeCount;
        std::vector<int>    mRandomNumber;
};

static int          InitBot(std::string IpAddress, std::string Port, std::string Password);
static void         ExecBotLoop(int socket, std::string& Buffer);
static void         AddBuffer(int socket, std::string& Buffer, std::string buffer, bool& registStatus, std::vector<Bot>& BotList);
static std::string  makeCommand(std::string& Buffer);
static void         ExecMessage(int socket, std::string msg, bool& registStatus, std::vector<Bot>& BotList);
static std::string  FindCommand(std::string& msg);
static bool         CheckCommand(const std::string& Buffer);
static void         Ping(int socket, std::string& msg);
static void         Invite(int socket, std::string& msg, std::vector<Bot>& BotList);
static void         Join(int sock, std::string& msg, std::vector<Bot>& BotList);
static void         Part(std::string& msg, std::vector<Bot>& BotList);
static void         Privmsg(std::string& msg, std::vector<Bot>& BotList);
static bool         isTryDigit(std::string& number);