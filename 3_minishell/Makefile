NAME			:= minishell
LIBFT_DIR 		:= libft/
LIBFT 			:= $(LIBFT_DIR)libft.a
CC				:= cc
CFLAGS			:= -Wall -Werror -Wextra

READLINE		:= -lreadline -L${HOME}/.brew/opt/readline/lib
READLINE_OBJ	:= -I${HOME}/.brew/opt/readline/include

TOKENIZER		:=	tokenizer/tokenizer.c \
					tokenizer/tokenizer_utils.c \
					tokenizer/input_type.c \
					tokenizer/input_type_2.c \
					tokenizer/input_type_3.c

PARSER			:=	parser/parser.c \
					parser/p_grammer.c \
					parser/p_grammer_2.c \
					parser/p_utils.c \
					parser/p_utils_2.c \
					parser/p_syntax_error.c \

BUILTIN			:=	builtin/cd.c \
					builtin/echo.c \
					builtin/env.c \
					builtin/exit.c \
					builtin/export.c \
					builtin/export_utils.c \
					builtin/pwd.c \
					builtin/unset.c

EXPANSION		:=	expansion/expansion.c \
					expansion/env_utils.c \
					expansion/expansion_utils.c \
					expansion/new_cmd_utils.c \
					expansion/env_expand.c \
					expansion/expansion_utils_2.c \
					expansion/expansion_utils_3.c \
					expansion/quote_expand.c \
					expansion/wild_card.c \
					expansion/new_cmd_utils_2.c \
					expansion/wild_card_2.c \
					expansion/wild_card_3.c
         
EXECUTION		:=	execution/execution.c \
 					execution/e_and_or_if.c \
					execution/e_builtin.c \
					execution/e_cmd_utils.c \
 					execution/e_cmd.c \
					execution/e_pipe.c \
					execution/e_redir_here_doc.c \
 					execution/e_redir_utils.c \
					execution/e_redir.c \
					execution/e_subshell.c \
					execution/e_utils.c

SIGNAL			:= signal/signal.c \
				   signal/signal_utils.c

SRC_MAN			:=  main.c \
					$(TOKENIZER) \
        		 	$(PARSER) \
        			$(EXPANSION) \
					$(BUILTIN) \
					$(EXECUTION) \
					$(SIGNAL)

GREEN = \033[0;92m
BLUE = \033[0;94m
WHITE = \033[0;97m
PURPLE = \033[1;35m

ifdef WITH_BONUS
	SRC_FIN = $(SRC_BONUS)
else
	SRC_FIN = $(SRC_MAN)
endif

OBJS	:=	$(SRC_FIN:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -Iinc -Ilibft $(READLINE_OBJ)

all: 
	@make -sC $(LIBFT_DIR)
	@make $(NAME)

bonus:
	@make WITH_BONUS=1

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE)

ifdef WITH_BONUS
	@echo "$(PURPLE)🐚 minishell make bonus done!$(WHITE)"
else
	@echo "$(GREEN)🐚 minishell make done!$(WHITE)"
endif

clean:
	@make clean -sC $(LIBFT_DIR)
	@rm -f $(SRC_MAN:.c=.o)
	@rm -f $(SRC_BONUS:.c=.o)
	@echo "$(BLUE)🐚 minishell clean done!$(WHITE)"

fclean:
	@make fclean -sC $(LIBFT_DIR) 
	@rm -f $(SRC_MAN:.c=.o)
	@rm -f $(SRC_BONUS:.c=.o)
	@rm -f $(NAME)
	@echo "$(BLUE)🐚 minishell fclean done!$(WHITE)"

re: fclean all

.PHONY: all clean fclean re bonus
