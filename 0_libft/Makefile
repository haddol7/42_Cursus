NAME := libft.a
SRCS := ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_strncmp.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c
OBJS := $(SRCS:.c=.o)
SRCS_B := ft_lstnew_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstiter_bonus.c\
		ft_lstmap_bonus.c
OBJS_B := $(SRCS_B:.c=.o)

AR := ar
ARFLAGS := -rc

CC := cc
CFLAGS := -Wall -Wextra -Werror

ifdef WITH_BONUS
	OBJ_FIN = $(OBJS) $(OBJS_B)
else
	OBJ_FIN = $(OBJS)
endif

all : $(NAME)

bonus : 
	make WITH_BONUS=1

clean :
	rm -f $(OBJS) $(OBJS_B)
fclean : clean
	rm -f $(NAME)
re : fclean all

$(NAME) : $(OBJ_FIN)
	$(AR) $(ARFLAGS) $@ $?

%.o : %.c
	$(CC) $(CFLAGS) -c $<

.PHONY : all bonus clean fclean re
