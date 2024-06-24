NAME			:= minishell
LIBFT_DIR 		:= libft/
LIBFT 			:= $(LIBFT_DIR)libft.a
CC				:= cc
CFLAGS			:= -Wall -Werror -Wextra -g

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
					main_utils.c \
					$(TOKENIZER) \
        		 	$(PARSER) \
        			$(EXPANSION) \
					$(BUILTIN) \
					$(EXECUTION) \
					$(SIGNAL)

TOKENIZER_BONUS		:=	bonus/tokenizer/tokenizer_bonus.c \
					bonus/tokenizer/tokenizer_utils_bonus.c \
					bonus/tokenizer/input_type_bonus.c \
					bonus/tokenizer/input_type_2_bonus.c \
					bonus/tokenizer/input_type_3_bonus.c

PARSER_BONUS		:=	bonus/parser/parser_bonus.c \
					bonus/parser/p_grammer_bonus.c \
					bonus/parser/p_grammer_2_bonus.c \
					bonus/parser/p_utils_bonus.c \
					bonus/parser/p_utils_2_bonus.c \
					bonus/parser/p_syntax_error_bonus.c \

BUILTIN_BONUS		:=	bonus/builtin/cd_bonus.c \
					bonus/builtin/echo_bonus.c \
					bonus/builtin/env_bonus.c \
					bonus/builtin/exit_bonus.c \
					bonus/builtin/export_bonus.c \
					bonus/builtin/export_utils_bonus.c \
					bonus/builtin/pwd_bonus.c \
					bonus/builtin/unset_bonus.c

EXPANSION_BONUS		:=	bonus/expansion/expansion_bonus.c \
					bonus/expansion/env_utils_bonus.c \
					bonus/expansion/expansion_utils_bonus.c \
					bonus/expansion/new_cmd_utils_bonus.c \
					bonus/expansion/env_expand_bonus.c \
					bonus/expansion/expansion_utils_2_bonus.c \
					bonus/expansion/expansion_utils_3_bonus.c \
					bonus/expansion/quote_expand_bonus.c \
					bonus/expansion/wild_card_bonus.c \
					bonus/expansion/new_cmd_utils_2_bonus.c \
					bonus/expansion/wild_card_2_bonus.c \
					bonus/expansion/wild_card_3_bonus.c
         
EXECUTION_BONUS		:=	bonus/execution/execution_bonus.c \
 					bonus/execution/e_and_or_if_bonus.c \
					bonus/execution/e_builtin_bonus.c \
					bonus/execution/e_cmd_utils_bonus.c \
 					bonus/execution/e_cmd_bonus.c \
					bonus/execution/e_pipe_bonus.c \
					bonus/execution/e_redir_here_doc_bonus.c \
 					bonus/execution/e_redir_utils_bonus.c \
					bonus/execution/e_redir_bonus.c \
					bonus/execution/e_subshell_bonus.c \
					bonus/execution/e_utils_bonus.c

SIGNAL_BONUS		:= bonus/signal/signal_bonus.c \
				  	bonus/signal/signal_utils_bonus.c

SRC_BONUS			:=  bonus/main_bonus.c \
					$(TOKENIZER_BONUS) \
        		 	$(PARSER_BONUS) \
        			$(EXPANSION_BONUS) \
					$(BUILTIN_BONUS) \
					$(EXECUTION_BONUS) \
					$(SIGNAL_BONUS)

GREEN = \033[0;92m
BLUE = \033[0;94m
WHITE = \033[0;97m
PURPLE = \033[1;35m

ifdef WITH_BONUS
	SRC_FIN = $(SRC_BONUS)
	INC_FLAG = -Ibonus/inc
else
	SRC_FIN = $(SRC_MAN)
	INC_FLAG = -Iinc
endif

OBJS	:=	$(SRC_FIN:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAG) -Ilibft $(READLINE_OBJ)

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
