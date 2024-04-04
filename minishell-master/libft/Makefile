CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Wpedantic -Wtype-limits -g
NAME = libft.a
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_printf.c ft_printf_utils.c ft_putnbr_fd_us.c ft_split_printf.c ft_printf_utils2.c ft_printf_write_funcs.c ft_printf_write_funcs2.c ft_printf_write_funcs3.c ft_split_printf2.c get_next_line.c get_next_line_utils.c ft_free_split.c vec.c vec_iterators.c vec_operations.c vec_quicksort.c vec_strlcat.c vec_utils.c vec_split.c ft_isspace.c

BONUS_SRCS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
all: $(NAME)

$(NAME): $(OBJS) $(BONUS_OBJS)
	ar -rc $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
