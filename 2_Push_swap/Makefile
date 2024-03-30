NAME := push_swap

SRC_DIR := src/
OBJ_DIR := obj/
CC := cc
CFLAGS := -Wall -Werror -Wextra 
CFLAGS := 


LIB := lib/
PRINTF_DIR := $(LIB)ft_printf/
PRINTF := $(PRINTF_DIR)libftprintf.a

LIBFT_DIR := $(LIB)libft/
LIBFT := $(LIBFT_DIR)libft.a

HEADER  := -I$(PRINTF_DIR) -I$(LIBFT_DIR)

SRC_FILES =	deque main

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

GREEN = \033[0;92m
BLUE = \033[0;94m
WHITE = \033[0;97m

all: makelibs
	@mkdir -p obj
	@$(MAKE) $(NAME)

makelibs:
	@$(MAKE) -C $(PRINTF_DIR)
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ $(PRINTF) $(LIBFT) -o $@
	@echo "$(GREEN)📺 push_swap : make done!$(WHITE)"	

bonus:
	@$(MAKE) all

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@ $(HEADER)
	
clean:
	@make clean -C $(LIBFT_DIR) 
	@make clean -C $(PRINTF_DIR)
	rm -rf $(OBJ_DIR)
	@echo "$(BLUE)📺 push_swap : clean done!$(WHITE)"

fclean:
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	@echo "$(BLUE)📺 push_swap : clean done!$(WHITE)"
	@echo "$(BLUE)📺 push_swap : fclean done!$(WHITE)"

re: fclean
	@$(MAKE)	

-include $(DEPS)

.PHONY: all clean fclean re

