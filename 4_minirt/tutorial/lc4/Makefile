.SUFFIXES : .c .o

NAME = a.out

CC = cc
CFLAGS = -Wall -Wextra -Werror
MEMORY = -g3 -fsanitize=address
LLDB = -g

RM = rm -f
INCLUDE = -I./include

SRCS = src/print/print.c \
	src/scene/canvas.c \
	src/scene/object_create.c \
	src/trace/ray/ray.c \
	src/trace/hit/hit_sphere.c \
	src/main.c \
	src/utils.c
	
OBJS = $(SRCS:.c=.o)

all: $(NAME)
	@make clean

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
