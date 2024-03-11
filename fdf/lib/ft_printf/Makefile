NAME := libftprintf.a
SRCS := ft_printf.c\
		ft_printf_utils.c\
        parse_flag.c\
		make_conversion.c\
		make_field.c\
		make_field_join.c\
		make_speci.c\
		make_speci_2.c
OBJS := $(SRCS:.c=.o)

BOLD_PURPLE	=	\033[1;35m
BOLD_CYAN	=	\033[1;36m
BOLD_YELLOW	=	\033[1;33m
NO_COLOR	=	\033[0m
DEF_COLOR 	= \033[0;39m
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

AR := ar
ARFLAGS := -rc

CC := cc
CFLAGS := -Wall -Wextra -Werror

all : $(NAME)

bonus : $(NAME)

clean :
	@rm -f $(OBJS)
	@echo "$(BLUE)📝 printf : clean done!$(WHITE)"
fclean : clean
	@rm -f $(NAME)
	@echo "$(BLUE)📝 printf : fclean done!$(WHITE)"
re : fclean all

$(NAME) : $(OBJS)
	@$(AR) $(ARFLAGS) $@ $?
	@echo "$(GREEN)📝 printf : make done!$(WHITE)"

%.o : %.c
	@$(CC) $(CFLAGS) -c $<

.PHONY : all bonus clean fclean re
