.SUFFIXES : .c .o

NAME = a.out

CC = cc
CFLAGS = -Werror -Wall -Wextra
MEMORY = -g3
LLDB = -g

RM = rm -f
INCLUDE = -I./include

SRCS = src/print/print.c \
	src/scene/canvas.c \
	src/scene/object_create.c \
	src/trace/hit/hit_sphere.c \
	src/trace/hit/hit.c \
	src/trace/hit/normal.c \
	src/trace/ray/phong_lighting.c \
	src/trace/ray/ray.c \
	src/utils/objects_utils.c \
	src/utils/utils.c \
	src/main.c
	
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
