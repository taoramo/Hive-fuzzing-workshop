/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:26:41 by toramo            #+#    #+#             */
/*   Updated: 2024/01/15 16:29:44 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif
# ifndef FD_MAX
#  define FD_MAX 256
# endif
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_printf
{
	va_list	arg_ptr;
	void	*arg;
	int		alt;
	int		zero;
	int		minus;
	int		plus;
	int		space;
	int		dot;
	int		width;
	int		precision;
	char	type;
	int		written;
}	t_printf;

typedef struct s_vec
{
	unsigned char	*memory;
	size_t			elem_size;
	size_t			alloc_size;
	size_t			len;
}	t_vec;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *string, const char *substring, size_t len);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *src);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *newlst);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *newlst);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int			ft_free_split(char **arr);

char		*get_next_line(int fd);
void		*ft_memmove_gnl(void *dst, const void *src, size_t len);
int			ft_strlen_gnl(char *str, int len, int flag);
char		*cp_and_move(char *str, int *strlen, int *in_buffer, char *buf);
char		*gnl_insert_null(char *str, int strlen);
char		*free_if_exists(char *str, int *in_buffer);

int			ft_printf(const char *s, ...);
int			count_words_printf(const char *s);
char		**ft_free_arr_printf(char **strs, int i);
int			ft_strlen_printf(const char *s);
void		printf_write_null(t_printf *tab);
int			ft_abs(int i);
void		reset_printf_tab(t_printf *tab);
void		printf_write_percentage(t_printf *tab);
char		**ft_split_printf(const char *s);
char		**ft_free_arr(char **strs, int i);
int			free_printf_mem(t_printf *tab, char **strs);
void		printf_assign_flags(char *str, t_printf *tab, int i);
void		update_tab(char *str, t_printf *tab, va_list arg_ptr);
void		write_pad_chars(char c, int i, t_printf *tab);
void		printf_write_char(t_printf *tab);
void		printf_write_string(t_printf *tab);
int			int_str_size_printf(int n, t_printf *tab);
void		printf_write_int(t_printf *tab);
void		printf_write_int2(t_printf *tab, char pad,
				int padsize, int intlength);
int			int_str_size_printf_us(unsigned int n, t_printf *tab);
void		printf_write_int_us(t_printf *tab);
void		pointer_to_hex_str(char *str, unsigned long int n);
void		unsigned_to_hex_str(char *str,
				unsigned int n, t_printf *tab, int i);
void		printf_write_pointer(t_printf *tab);
int			ft_hexlength(char *str, t_printf *tab);
void		printf_write_hex(t_printf *tab);
void		printf_write_hex2(t_printf *tab, char *str, int padsize, char pad);
void		conversion(char *str, t_printf *tab, va_list arg_ptr);
t_printf	*ft_init_printf_tab(void);
void		ft_putnbr_fd_us(unsigned int nb, int fd);

int			vec_new(t_vec *src, size_t init_len, size_t elem_size);
void		vec_free(t_vec *src);
int			vec_from(t_vec *dst, void *src, size_t len, size_t elem_size);
int			vec_resize(t_vec *src, size_t target_size);
int			vec_clear(t_vec *src);
int			vec_push(t_vec *src, void *elem);
int			vec_pop(void *dst, t_vec *src);
int			vec_copy(t_vec *dst, t_vec *src);
void		*vec_get(t_vec *src, size_t index);
int			vec_insert(t_vec *dst, void *elem, size_t index);
int			vec_remove(t_vec *src, size_t index);
int			vec_append(t_vec *dst, t_vec *src);
int			vec_prepend(t_vec *dst, t_vec *src);
void		vec_iter(t_vec *src, void (*f) (void *));
void		*vec_find(t_vec *src, int (*f) (void *));
int			vec_map(t_vec *dst, t_vec *src, void (*f) (void *));
int			vec_filter(t_vec *dst, t_vec *src, int (*f) (void *));
void		vec_reduce(void *acc, t_vec *src, void (*f) (void *, void *));
void		vec_sort(t_vec *src, int (*f)(void *, void *));
void		*ft_calloc(size_t count, size_t size);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *str, int c, size_t n);
int			vec_strlcat(t_vec *dst, char *src, size_t l);
int			free_split_vec(t_vec *strs);
int			ft_strlen_member(const char *str, char sep);
void		vec_print_elem_str(void *elem);
int			vec_split(t_vec *dst, const char *s, char c);
int			vec_dup(t_vec *dst, t_vec *src);
#endif
