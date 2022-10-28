#ifndef MINISHELL_H
#define MINISHELL_H

#include "../lib/libft.h"
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
	NADA,
	R_OUT,
	R_IN,
	R_APP,
	PIPE,
	HEREDOC,
};

struct	s_file
{
	char		*filename;
	int			fd;
	int			(*create)(int fd[2], char *path, int mode);
	void		(*close)(int fd[2]);
	t_type		type;
};

struct	s_cmd
{
	char			*cmd;
	char			**args;
	t_type			type;
	t_file			*file;
	t_cmd			*next;
};

typedef struct s_envp
{
	char		**envp;
	t_cmd		*head;
	char		*path;
	int			exit_code;
	bool		valid_input;
}				t_envp;

extern t_envp	g_envp;



//cmd_build.c
void	build_cmds(char **cmds);

//parse.c
int 	ft_strcount_char(char *str, char l);
char	**line_to_arrays(char *line);

//parse_clean.c //for late to remove quotes- but we will do this at the very end
char 	*parse_clean(char *str);
void	dollar_for_money(char **outup, char **input);

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



#endif