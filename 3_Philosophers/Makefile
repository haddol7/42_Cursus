MAN_DIR := philo/
BONUS_DIR := philo_bonus/
OBJ_DIR := obj/
CC := cc
CFLAGS := -Wall -Werror -Wextra

SRC_MAN	= main 
SRC_BONUS = main_bonus

ifdef WITH_BONUS
	NAME = philo_bonus/philo_bonus
	SRC_FIN = $(SRC_BONUS)
	SRC_DIR = $(BONUS_DIR)
else
	NAME = philo/philo
	SRC_FIN = $(SRC_MAN)
	SRC_DIR = $(MAN_DIR)
endif

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FIN)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FIN)))
DEP = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FIN)))

GREEN = \033[0;92m
BLUE = \033[0;94m
WHITE = \033[0;97m
PURPLE = \033[1;35m

all:
	@mkdir -p obj
	@make $(NAME)

bonus:
	@make WITH_BONUS=1

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

ifdef WITH_BONUS
	@echo "$(PURPLE)🍴 philosophers : make bonus done!$(WHITE)"
else
	@echo "$(GREEN)🍴 philosophers : make done!$(WHITE)"
endif

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@ $(HEADER)
	
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)🍴 philosophers : clean done!$(WHITE)"

fclean:
	@rm -rf $(OBJ_DIR)
	@rm -f philo/philo
	@rm -f philo_bonus/philo_bonus
	@echo "$(BLUE)🍴 philosophers : fclean done!$(WHITE)"

re: fclean
	@make

-include $(DEP)

.PHONY: all clean fclean re bonus
