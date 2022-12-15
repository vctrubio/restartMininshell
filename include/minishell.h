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
	NADA,
	R_OUT,
	R_IN, //NOT USING/CALLING ATM
	R_APP,
	HEREDOC,
};

struct					s_file
{
	char				*filename;
	char				*heredoc;
	int					fd;
	t_type				type;
	t_file				*next;
};

struct					s_cmd
{
	char				**args;
	t_type				type;
	t_file				*file;
	t_file				*heredoc;
	t_file				*file_in;
	t_cmd				*next;
	t_cmd				*prev;
	id_t				flag;
	int					fd_in;
};

typedef struct s_envp
{
	char				**envp;
	t_cmd				*head;
	int					exit_code;
	bool				valid_input;
}						t_envp;

typedef struct s_vars
{
	int					i;
	int					j;
	int					k;
	int					l;
	int					m;
	int					start;
	int					end;
	int					size;
	int					inner_quote;
	int					outer_quote;
	char				*ptr2str;
	char				*ptr2char;
	char				***p2p2p;
	char				*str;
	char				*str2;
	char				*tmp_str;
	char				*tmp_str2;
	char				**matrix;
	char				**matrix2;
	char				**tmp_matrix;
	char				**tmp_matrix2;

}						t_vars;

//array.c
void					print_tcmd(t_cmd *cmd);
void					print_arrays(char **a);
void					free_arrays(char **arr);

//built_ins.c
int						ft_pwd(char **argv);
int						ft_echo(char **argv);
int						ft_cd(char **argv);
int						ft_export(char **argv);

//built_ins_background.c
int						ft_setenv(char *name, char *value, int overwrite);
int	set_cd_folder_return_if_free_folder_or_not(char **argv,
												char **ptr2folder);
void					ft_export_no_args(void);
int						ft_unset(char **argv);

//built_ins_checkers_n_runners.c
int						check_if_builtin_not_pipe(t_cmd *cmd);
int						check_if_builtin_2pipe(t_cmd *cmd);
int						run_builtin_not_piped(t_cmd *cmd);
int						run_builtin_2pipe(t_cmd *cmd);

//concat.c
char					*ft_concat3(char *s1, char *s2, char *s3);
char					*ft_concat_string_between_chars(char c_start, char *s,
							char c_end);
char					*ft_concat_multi_getsize_n_alloc(char **s, char *glue);
char					*ft_concat_multi(char **s, char *glue);

//cmd_build.c
bool					add_cmds(char **matrix);
void					build_cmds(char **matrix);

//exec.c
void					loop_execution(t_cmd *ptr);

//free.c
void					free_cmds(t_cmd *first);

//heredoc.c
void					init_heredoc(void);

//initializers.c
void					ft_inicialize_vars(t_vars *vars);
t_cmd					*ft_inicialize_cmd(char **matrix);

//matrix_fts.c
char					**ft_matrix_dup(char **matrix, int push);
int						ft_matrix_get_num_col(char **matrix);
char					**ft_matrix_push(char **matrix, char *str);
void					ft_matrix_free(char **matrix);

//matrix_utils.c
char	**ft_matrix_remove_col_by_index(char **matrix,
										int index);
void	ft_print_matrix_add_str2line_start(char **matrix,
										char *str,
										char *glue);
void	ft_chk_n_exit_if_null_ppchar(char **matrix,
									char *error_str);
void					ft_chk_n_exit_if_null_pchar(char *str, char *error_str);

//path.c
int						ft_get_exec_path_chk_access(char *path, char **env_path,
							char ***matrix);
char					*ft_get_exec_path(char **argv);
char					*ft_getenv(char *name, int trimmed);

//parse.c
int						ft_strcount_char(char *str, char l);
char					**line_to_matrix(char *line);

//parse_clean.c //for late to remove quotes- but we will do this at the very end
char					*parse_clean(char **p2str);
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

//utils_fd
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putchar_fd(char c, int fd);

//utils2.c
int						ft_isalnum(int c);
void					ft_swap2str(char **str1, char **str2);

//validate.c
void					validate_rl(char **matrix);

//var_expansion.c
int						ft_is_var_from_expansion(char *str, t_vars *vars);
t_vars					ft_exp_helper(t_vars v, char *str);
t_vars					ft_nexp_helper(t_vars v, char *str);
char					*ft_var_expansion(char *str);

void					ft_get_quotes_inner_outer(char c, t_vars *vars);

#endif