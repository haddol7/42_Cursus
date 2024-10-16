NAME = ex03

SRCS = Form.cpp PresidentialPardonForm.cpp ShrubberyCreationForm.cpp Bureaucrat.cpp RobotomyRequestForm.cpp main.cpp Intern.cpp
OBJS = ${SRCS:.cpp=.o}

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address

all: $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
