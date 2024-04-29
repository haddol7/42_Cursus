NAME := pipex
SRC_DIR := src/
OBJ_DIR := obj/
CC := cc
CFLAGS := -Wall -Werror -Wextra
LIB := lib/
PRINTF_DIR := $(LIB)ft_printf/
PRINTF := $(PRINTF_DIR)libftprintf.a
LIBFT_DIR := $(LIB)libft/
LIBFT := $(LIBFT_DIR)libft.a
HEADER := -I$(PRINTF_DIR) -I$(LIBFT_DIR) -Iinc/

SRC_MAN	= main pipex_utils exec_proc
SRC_BONUS = 

ifdef WITH_BONUS
	SRC_FIN = $(SRC_BONUS)
else
	SRC_FIN = $(SRC_MAN)
endif

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FIN)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FIN)))
DEP = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FIN)))

GREEN = \033[0;92m
BLUE = \033[0;94m
WHITE = \033[0;97m
PURPLE = \033[1;35m

all:
	@make -sC $(LIBFT_DIR)
	@make -sC $(PRINTF_DIR)
	@mkdir -p obj
	@make $(NAME)

# bonus:
# 	@make WITH_BONUS=1

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ $(PRINTF) $(LIBFT) -o $@

ifdef WITH_BONUS
	@echo "$(PURPLE) 🍴 pipex : make bonus done!$(WHITE)"
else
	@echo "$(GREEN)🍴 pipex : make done!$(WHITE)"
endif

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@ $(HEADER)
	
clean:
	@make clean -sC $(LIBFT_DIR) 
	@make clean -sC $(PRINTF_DIR)
	rm -rf $(OBJ_DIR)
	@echo "$(BLUE)🍴 pipex : clean done!$(WHITE)"

fclean:
	@make fclean -sC $(LIBFT_DIR) 
	@make fclean -sC $(PRINTF_DIR)
	rm -rf $(OBJ_DIR)
	rm -f pipex
	@echo "$(BLUE)🍴 pipex : fclean done!$(WHITE)"

re: fclean
	@make	

-include $(DEP)

.PHONY: all clean fclean re bonus

