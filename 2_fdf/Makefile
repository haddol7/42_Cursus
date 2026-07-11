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

GREEN = \033[0;92m
BLUE = \033[0;94m
WHITE = \033[0;97m

all: makelibs
	@mkdir -p obj
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
	
clean:
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR) 
	@make clean -C $(PRINTF_DIR)
	rm -rf $(OBJ_DIR)
	@echo "$(BLUE)📺 fdf : clean done!$(WHITE)"

fclean:
	@make clean -C $(MLX_DIR)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	@echo "$(BLUE)📺 fdf : clean done!$(WHITE)"
	@echo "$(BLUE)📺 fdf : fclean done!$(WHITE)"

re: fclean
	@$(MAKE)	

-include $(DEPS)

.PHONY: all clean fclean re

