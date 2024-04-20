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

SRC_COMMON = deque parse_elem command_1 command_2 command_3 push_swap_utils_1 push_swap_utils_2
SRC_MAN	= main \
		quick_sort quick_sort_split \
		base_case_a base_case_b_1 base_case_b_2 \
		small_sort
SRC_BONUS = main_bonus command_bonus

ifdef WITH_BONUS
	SRC_FIN = $(SRC_COMMON) $(SRC_BONUS)
	NAME = checker
else
	SRC_FIN = $(SRC_COMMON) $(SRC_MAN)
	NAME = push_swap
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

bonus:
	@make WITH_BONUS=1

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ $(PRINTF) $(LIBFT) -o $@

ifdef WITH_BONUS
	@echo "$(PURPLE)🥞 push_swap : make bonus done!$(WHITE)"
else
	@echo "$(GREEN)🥞 push_swap : make done!$(WHITE)"
endif

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@ $(HEADER)
	
clean:
	@make clean -sC $(LIBFT_DIR) 
	@make clean -sC $(PRINTF_DIR)
	rm -rf $(OBJ_DIR)
	@echo "$(BLUE)🥞 push_swap : clean done!$(WHITE)"

fclean:
	@make fclean -sC $(LIBFT_DIR) 
	@make fclean -sC $(PRINTF_DIR)
	rm -rf $(OBJ_DIR)
	rm -f push_swap
	rm -f checker
	@echo "$(BLUE)🥞 push_swap : fclean done!$(WHITE)"

re: fclean
	@make	

-include $(DEP)

.PHONY: all clean fclean re bonus

