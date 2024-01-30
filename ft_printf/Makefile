NAME := libftprintf.a
SRCS := ft_printf.c\
        parse.c\
		make.c\
		make_field.c\
		make_field_2.c\
		make_speci.c\
		make_speci_2.c\
		utils.c
OBJS := $(SRCS:.c=.o)

AR := ar
ARFLAGS := -rc

CC := cc
CFLAGS := -Wall -Wextra -Werror

all : $(NAME)

bonus : $(NAME)

clean :
	rm -f $(OBJS)
fclean : clean
	rm -f $(NAME)
re : fclean all

$(NAME) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $?

%.o : %.c
	$(CC) $(CFLAGS) -c $<

.PHONY : all bonus clean fclean re
