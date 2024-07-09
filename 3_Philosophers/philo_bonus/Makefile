NAME := philo_bonus
SRC_DIR := src/
OBJ_DIR := obj/
CC := cc
CFLAGS := -Werror -Wall -Wextra -g

SRC_FILE = main_bonus init_bonus procs_bonus procs_monitor_bonus procs_philo_bonus utils_bonus

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILE)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILE)))
DEP = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILE)))

GREEN = \033[0;92m
BLUE = \033[0;94m
WHITE = \033[0;97m
PURPLE = \033[1;35m

all:
	@mkdir -p obj
	@make $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "$(PURPLE)🍴 philosophers : make bonus done!$(WHITE)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@
	
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)🍴 philosophers : clean done!$(WHITE)"

fclean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@echo "$(BLUE)🍴 philosophers : fclean done!$(WHITE)"

re: fclean
	@make

-include $(DEP)

.PHONY: all clean fclean re bonus
