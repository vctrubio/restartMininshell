#include "../include/minishell.h"
//static calls

t_envp	*_shell(void)
{
	static t_envp	enviroment;

	return (&enviroment);
}

void	init_shell(char **ev)
{
	t_envp	*shell;

	shell = _shell();
	shell->envp = ft_matrix_dup(ev, 0);
	shell->exit_code = 0;
	shell->exit = 0;
}

void	close_shell(void)
{
	if (_shell()->head)
		free_cmds(_shell()->head);
	if (_shell()->envp)
		//free_arrays(_shell()->envp);
		ft_matrix_free(_shell()->envp);
}
