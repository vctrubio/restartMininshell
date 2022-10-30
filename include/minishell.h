#ifndef MINISHELL_H
#define MINISHELL_H

# include "../lib/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>


typedef struct s_file	t_file;
typedef struct s_cmd	t_cmd;
typedef enum s_type		t_type;

enum	s_type
{
	NADA, // ls -la
	R_OUT, //ls -la > out.file
	R_IN, // cat < in.file
	R_APP, // ls -la >> out.file
	PIPE, // ls -la | grep b
	HEREDOC, 
};

struct	s_file
{
	char		*filename; //file.txt
	int			fd; //File
	int			(*create)(int fd[2], char *path, int mode);
	void		(*close)(int fd[2]);
	t_type		type; //R_OUT 
};

struct	s_cmd //echo -n hello world > file.txt 
{
	char			*cmd; // echo
	char			**args; // [-n] [hello] [world] [0]
	int				fd; 
	t_type			type; // R_OUT
	t_file			*file; // file
	t_cmd			*next; 
	t_cmd			*prev; 
};

typedef struct s_envp
{
	char		**envp;
	t_cmd		*head;
	char		*path;
	int			exit_code;
	bool		valid_input;
}				t_envp;

// typedef struct s_vars
// {
// 	int			i;
// 	int			j;
// 	int			k;
// 	int			l;
// 	int			m;
// 	int			start;
// 	int			end;
// 	int			size;
// 	char		*tmp_str;
// }				t_vars;

extern t_envp	g_envp;

//cmd_build.c
void	build_cmds(char **cmds);

//matrix
void	*ft_realloc(void *ptr, size_t size);
char	**ft_matrix_dup(char **matrix, int push);
char	**ft_matrix_push(char **matrix, char *str);
void	ft_chk_n_exit_if_null_ppchar(char **matrix, char *error_str);
void	ft_chk_n_exit_if_null_pchar(char *str, char *error_str);
int		ft_matrix_get_num_col(char **matrix);
char	**ft_matrix_dup(char **matrix, int push);
char	**ft_matrix_push(char **matrix, char *str);
void	ft_matrix_free(char **matrix);
char	**ft_matrix_remove_col_by_index(char **matrix, int index);
void	ft_print_matrix_add_str2line_start(char **matrix, char *str, char *glue);
void	ft_swap2str(char **str1, char **str2);


//parse.c
int 	ft_strcount_char(char *str, char l);
char	**line_to_arrays(char *line);

//parse_clean.c //for late to remove quotes- but we will do this at the very end
char 	*parse_clean(char *str);
void	dollar_for_money(char **outup, char **input);

//parse_envp.c
void	init_envp(char **envp);
int		ft_env(char **argv);

//static.c


//utils.c
int ft_strcount_char(char *str, char l);
int is_redir(int c);
int r_size(char *s);

//array.c
void	print_arrays(char **a);
void	free_arrays(char **arr);

//validate.c
void	validate_rl(char **matrix);

//utils_fd
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

#endif