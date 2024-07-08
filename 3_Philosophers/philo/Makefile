NAME := philo
SRC_DIR := src/
OBJ_DIR := obj/
CC := cc
CFLAGS :=

SRC_FILE	= main init utils thread thread_monitor thread_philo

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
	@echo "$(GREEN)🍴 philosophers : make done!$(WHITE)"

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

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
