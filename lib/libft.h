#ifndef	LIBFT_H
# define	LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>

#define	BUFFER_SIZE 2

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

bool	ft_strexact(char *s1, char *s2);
void 	ft_stradd(char **str, char *add);
void	*ft_memset(void *str, char c, size_t l);
int		ft_strlen(char *str);
char	*ft_substr(char *str, int begg, int l);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strnew(size_t size);
void	ft_putstr(char const *s);
void    ft_putchar(char c);
int		ft_isspace(char c);
void	ft_strclr(char *s);
char		**ft_strsplit(char const *s, char ch);
int		ft_strexist(char *s, char c);
void	ft_strfree(char **str);
char	*ft_str_offset(char *str, int i);
char	*ft_strnstr(const char	*str, const char *find, size_t len);
int		has_newline(char *str);
int		ft_d_counter(int n);
int		count_words(char *str, char c);
int		get_next_line(int fd, char **line);

#endif
