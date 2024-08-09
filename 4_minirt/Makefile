NAME := minirt

SRC_DIR := src/
CC := cc
# CFLAGS := -Wall -Werror -Wextra
CFLAGS :=

LIB := lib/
LIBFT_DIR := $(LIB)libft/
LIBFT := $(LIBFT_DIR)libft.a

MLX_DIR := $(LIB)mlx/
MLX := $(MLX_DIR)libmlx.dylib
MLXFLAGS := -L$(MLX_DIR) -framework OpenGL -framework AppKit

HEADER  := -I$(LIBFT_DIR) -I$(MLX_DIR) -Iinc/

SRCS_PRINT =	src/print/print.c

SRCS_SCENE =	src/scene/canvas.c \
				src/scene/object_create.c

SRCS_TRACE =	src/trace/hit/hit_sphere.c \
				src/trace/hit/hit.c \
				src/trace/hit/normal.c \
				src/trace/ray/phong_lighting.c \
				src/trace/ray/ray.c

SRCS_UTILS = 	src/utils/objects_utils.c \
				src/utils/utils.c

SRCS_MAP = src/parsing/validity.c

SRCS =			$(SRCS_PRINT) \
				$(SRCS_SCENE) \
				$(SRCS_TRACE) \
				$(SRCS_UTILS) \
				$(SRCS_MAP) \
				src/main.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

GREEN = \033[0;92m
BLUE = \033[0;94m
WHITE = \033[0;97m

all: makelibs
	@$(MAKE) $(NAME)

makelibs:
	@$(MAKE) -C $(MLX_DIR)
	@install_name_tool -id lib/mlx/libmlx.dylib lib/mlx/libmlx.dylib
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBFT) $(MLX) $(MLXFLAGS) -o $@
	@echo "$(GREEN)🌏 minirt : make done!$(WHITE)"	

bonus:
	@$(MAKE) all

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@ $(HEADER)
	
clean:
	rm -f $(OBJS) $(DEPS)
	@echo "$(BLUE)🌏 minirt : clean done!$(WHITE)"

fclean:
	@make clean -C $(MLX_DIR)
	@make fclean -C $(LIBFT_DIR)
	rm -f $(OBJS) $(DEPS)
	rm -f $(NAME)
	@echo "$(BLUE)🌏 minirt : fclean done!$(WHITE)"

re: fclean
	@$(MAKE)

-include $(DEPS)

.PHONY: all clean fclean re

