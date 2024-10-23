NAME := ircserv
CC := c++
CFLAGS := -Werror -Wall -Wextra -std=c++98 -Iinc/ -Iinc/message/ -fsanitize=address

SRC_DIR := src/
OBJ_DIR := obj/

#============== 소스 파일 ==============#
SRC_SERVER	=	$(SRC_DIR)server/Server.cpp

SRC_CLIENT	=	$(SRC_DIR)client/Client.cpp

SRC_MESSAGE =	$(SRC_DIR)message/AMessage.cpp \
				$(SRC_DIR)message/CommandTemplate.cpp \
				$(SRC_DIR)message/Nick.cpp \
				$(SRC_DIR)message/User.cpp \
				$(SRC_DIR)message/Pass.cpp \
				$(SRC_DIR)message/NoCommand.cpp \
				$(SRC_DIR)message/Privmsg.cpp \
				$(SRC_DIR)message/Join.cpp \

SRC_CHANNEL = 	$(SRC_DIR)channel/Channel.cpp

SRCS =			$(SRC_SERVER) \
				$(SRC_CLIENT) \
				$(SRC_MESSAGE) \
				$(SRC_CHANNEL) \
				$(SRC_DIR)main.cpp

OBJS = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCS))
DEPS = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.d, $(SRCS))
#============== 소스 파일 ==============#

GREEN = \033[0;92m
BLUE = \033[0;94m
WHITE = \033[0;97m
PURPLE = \033[1;35m

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "$(GREEN)💬 ft_irc : make done! 💬$(WHITE)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR)
	@echo "$(BLUE)💬 ft_irc : clean done! 💬$(WHITE)"

fclean:
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	@echo "$(BLUE)💬 ft_irc : fclean done! 💬$(WHITE)"

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re bonus
