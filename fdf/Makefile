NAME			:= fdf

SRC_DIR			:= src/
OBJ_DIR			:= obj/
CC				:= cc
CFLAGS			:= -Wall -Werror -Wextra
#FSANITIZE		:= -fsanitize=address -g

INC		 		:= inc/
LIB				:= lib/
PRINTF_DIR		:= $(LIB)ft_printf/
PRINTF			:= $(PRINTF_DIR)libftprintf.a

LIBFT_DIR		:= $(LIB)libft/
LIBFT			:= $(LIBFT_DIR)libft.a

MLX_DIR			:= $(LIB)minilibx/
MLX				:= $(MLX_DIR)libmlx.a
MLXFLAGS		:= -Imlx -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

HEADER 			:= -I$(INC) -I$(PRINTF_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

SRC_FILES		=	main

SRC 			= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 			= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 			= 	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))
INCS			= 	$(addprefix $(INCLUDE), $(addsuffix .h, $(INC_FILES)))

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

all: makelibs
	@$(MAKE) $(NAME)

makelibs:	
	@$(MAKE) -sC $(MLX_DIR)
	@$(MAKE) -sC $(PRINTF_DIR)
	@$(MAKE) -sC $(LIBFT_DIR)

$(NAME): $(OBJ)		
	@$(CC) $(CFLAGS) $(OBJ) $(PRINTF) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)📺 fdf : make done!"	

bonus:		
	@$(MAKE) all
			
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS)
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

$(PRINTF):
	@make -C $(PRINTF_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MINILIBX):
	@make -C $(MLX_DIR)

clean:
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR) 
	@make clean -C $(PRINTF_DIR)
	@rm -f $(OBJ) $(DEPS)
	@echo "$(BLUE)📺 fdf : clean done!"

fclean:
	@make clean -C $(MLX_DIR)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)
	@rm -f $(OBJ) $(DEPS)
	@echo "$(BLUE)📺 fdf : clean done!"
	@echo "$(BLUE)📺 fdf : fclean done!"

re: fclean 
	@$(MAKE)	

-include $(DEPS)

.PHONY: all clean fclean re

