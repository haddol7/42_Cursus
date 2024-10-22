#pragma once

//Replys
#define RPL_WELCOME(NICK, USER, HOST) (std::string("001") + " Welcome to the Internet Relay Network " + NICK + "!" + USER + "@" + HOST + "\r\n")
#define RPL_TOPIC(CHANNEL, TOPIC) (std::string("332") + " " + CHANNEL + " :" + TOPIC)

//Errors
#define ERR_NONICKNAMEGIVEN (std::string("431") + " :No nickname given")
#define ERR_ERRONEUSNICKNAME(NICK) (std::string("432") + " " + NICK + " :Erroneous nickname")
#define ERR_NICKNAMEINUSE(NICK) (std::string("433") + " " + NICK + " :Nickname is already in use")
#define ERR_NICKCOLLISION(NICK, USER, HOST) (std::string("436") + " " + NICK + " :Nickname collision KILL from " + USER + "@" + HOST)
#define ERR_UNAVAILRESOURCE(NAME, TYPE) (std::string("437") + " " + NAME + " :" + TYPE + " is temporarily unavailable") //can be used for both nick and channel
#define ERR_NEEDMOREPARAMS(COMMAND) (std::string("461") + " " + COMMAND + " :Not enough parameters")
#define ERR_ALREDYREGISTRED (std::string("462") + " :Unauthorized command (already registered)")
#define ERR_RESTRICTED (std::string("484") + " :Your connection is restricted!")

#define ERR_NORECIPIENT(COMMAND)	(std::string("411 ") + ":No recipient given " + COMMAND)
#define ERR_NOSUCHNICK(NICK)		(std::string("401 ") + NICK + " :No such nick/channel")
#define ERR_NOTEXTTOSEN				(std::string("412 ") + ":No text to send")
#define ERR_CANNOTSENDTOCHAN(CHAN)	(std::string("404 ") + CHAN + " :Cannot send to channel")
