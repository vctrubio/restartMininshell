#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_file	t_file;
typedef struct s_pipe	t_pipe;
typedef struct s_cmd	t_cmd;
typedef enum e_type		t_type;

enum					e_type
{
	NADA,  // ls -la
	R_OUT, //ls -la > out.file
	R_IN,  // cat < in.file
	R_APP, // ls -la >> out.file
	HEREDOC,
};

struct					s_file
{
	char 		*filename; //file.txt
	int 		fd;         //File
	t_type 		type;    //R_OUT
	t_file		*next; //ls>one>two
};

struct					s_cmd
{
	char				**args;
	t_type type;  // R_OUT
	t_file *file; // file
	t_cmd				*next;
	t_cmd				*prev;
	id_t				flag;
};

typedef struct s_envp
{
	char				**envp;
	t_cmd				*head;
	int					exit_code;
	bool				valid_input;
}						t_envp;

//free.c
void					free_cmds(t_cmd *first);

//cmd_build.c
void					add_cmds(char **matrix);
void					build_cmds(char **matrix);

//exec.c
void					loop_execution(t_cmd *ptr);
//matrix
char					**ft_matrix_dup(char **matrix, int push);
char					**ft_matrix_push(char **matrix, char *str);
void	ft_chk_n_exit_if_null_ppchar(char **matrix,
									char *error_str);
void					ft_chk_n_exit_if_null_pchar(char *str, char *error_str);
int						ft_matrix_get_num_col(char **matrix);
char					**ft_matrix_dup(char **matrix, int push);
char					**ft_matrix_push(char **matrix, char *str);
void					ft_matrix_free(char **matrix);
char	**ft_matrix_remove_col_by_index(char **matrix,
										int index);
void	ft_print_matrix_add_str2line_start(char **matrix,
										char *str,
										char *glue);
void					ft_swap2str(char **str1, char **str2);

//parse.c
int						ft_strcount_char(char *str, char l);
char					**line_to_matrix(char *line);

//parse_clean.c //for late to remove quotes- but we will do this at the very end
char					*parse_clean(char *str);
void					dollar_for_money(char **outup, char **input);

//parse_envp.c
int						ft_env(char **argv);

//shell.c
t_envp					*_shell(void);
void					init_shell(char **ev);
void					close_shell(void);

//utils.c
int						ft_strcount_char(char *str, char l);
int						is_redir(int c);
int						r_size(char *s);

//array.c
void					print_tcmd(t_cmd *cmd);
void					print_arrays(char **a);
void					free_arrays(char **arr);

//validate.c
void					validate_rl(char **matrix);

//utils_fd
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putchar_fd(char c, int fd);

//path.c
int						ft_get_exec_path_chk_access(char *path, char **env_path,
							char ***matrix);
char					*ft_get_exec_path(char **argv);
char					*ft_getenv(char *name, int trimmed);

//concat.c
char					*ft_concat3(char *s1, char *s2, char *s3);
char					*ft_concat_string_between_chars(char c_start, char *s,
							char c_end);
char					*ft_concat_multi_getsize_n_alloc(char **s, char *glue);
char					*ft_concat_multi(char **s, char *glue);

#endif