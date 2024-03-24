NAME := fdf

SRC_DIR := src/
OBJ_DIR := obj/
CC := cc
CFLAGS := -Wall -Werror -Wextra

LIB := lib/
PRINTF_DIR := $(LIB)ft_printf/
PRINTF := $(PRINTF_DIR)libftprintf.a

LIBFT_DIR := $(LIB)libft/
LIBFT := $(LIBFT_DIR)libft.a

MLX_DIR := $(LIB)mlx/
MLX := $(MLX_DIR)libmlx.dylib
MLXFLAGS := -L$(MLX_DIR) -framework OpenGL -framework AppKit

HEADER  := -I$(PRINTF_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

SRC_FILES =	color line_draw main map_conv map_draw map_load_utils map_load utils key_control

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

BOLD_PURPLE = \033[1;35m
BOLD_CYAN = \033[1;36m
BOLD_YELLOW	= \033[1;33m
NO_COLOR = \033[0m
DEF_COLOR = \033[0;39m
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: makelibs
	@$(MAKE) $(NAME)

makelibs:
	@$(MAKE) -C $(MLX_DIR)
	@install_name_tool -id lib/mlx/libmlx.dylib lib/mlx/libmlx.dylib
	@$(MAKE) -C $(PRINTF_DIR)
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)		
	$(CC) $(CFLAGS) $^ $(PRINTF) $(LIBFT) $(MLX) $(MLXFLAGS) -o $@
	@echo "$(GREEN)📺 fdf : make done!$(WHITE)"	

bonus:
	@$(MAKE) all
			
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@ $(HEADER)

$(PRINTF):
	@make -C $(PRINTF_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR)

clean:
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR) 
	@make clean -C $(PRINTF_DIR)
	rm -f $(OBJ) $(DEPS)
	@echo "$(BLUE)📺 fdf : clean done!$(WHITE)"

fclean:
	@make clean -C $(MLX_DIR)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)
	rm -f $(OBJ) $(DEPS)
	rm -f $(NAME)
	@echo "$(BLUE)📺 fdf : clean done!$(WHITE)"
	@echo "$(BLUE)📺 fdf : fclean done!$(WHITE)"

re: fclean
	@$(MAKE)	

-include $(DEPS)

.PHONY: all clean fclean re

