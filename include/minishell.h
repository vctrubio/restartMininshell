#ifndef MINISHELL_H
#define MINISHELL_H

#include "../lib/libft.h"


typedef enum	s_type
{
	NADA,
	R_OUT,
	R_IN,
	R_APP,
	PIPE,
}				t_type;


typedef struct	s_cmd
{
	char		*cmd;
	char		**args;
	t_type		type;
}				t_cmd;


typedef struct	s_shell
{
	int			exit_code;
}				t_shell;


//main.c


//parse.c


//static.c



#endif