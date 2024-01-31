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
