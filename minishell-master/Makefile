NAME = minishell

LIBFT = ./libft/libft.a

READLINE = -lreadline -L ~/.brew/opt/readline/lib -L/usr/local/opt/readline/lib

LIBS = $(LIBFT) $(READLINE)

INCLUDES = -I ~/.brew/opt/readline/include -I ./includes/ -I/usr/local/opt/readline/include -I./libft/

SRCS = $(addprefix srcs/, $(addprefix shell/, main.c parse_parentheses.c expand_supergroups.c minishell_vec_utils.c ft_is_inside.c signal.c error.c handle_pipelines.c syntax_check.c here_doc.c) \
	   $(addprefix commands/, prepare_command.c ft_isspace.c extract_files.c split_command.c split_expanded_command.c add_path.c run_command.c pipex.c pipe_commands.c pipe_commands2.c run_builtin.c) \
	   $(addprefix builtins/, builtins.c builtins2.c export.c export_utils.c cd.c) \
	   $(addprefix expand/, expand_envs.c wildcard.c wildcard2.c wildcard3.c remove_quotes.c))

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wunreachable-code -Wpedantic -Wtype-limits -g3 $(INCLUDES)

all: $(NAME)

$(OBJS): $(SRCS)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) $(CFLAGS) -o $(NAME)

$(LIBFT):
	make -C ./libft/

clean:
	rm -rf $(OBJS)
	make clean -C ./libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft/

re: fclean all

.PHONY: all, clean, fclean, re
