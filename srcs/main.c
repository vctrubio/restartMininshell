#include "../include/minishell.h"

void	add_cmds(char **matrix)
{
	validate_rl(matrix);
	if (_shell()->valid_input == false)
		printf("INVALID USER INPUT... ERROR IN PARSING... TBD\n");
	build_cmds(matrix);
	// free_arrays(matrix);
}

void	pre_execution(t_cmd *ptr)
{
}

void	do_execution(void)
{
	t_cmd	*ptr;
	char	**matrix;
	int		i;
	int		j;
	char	*path;
	int		pid;
	int		status;

	// if (status / 256 == 127)
	// {
	// }
	//return (status / 256);
	// pre_execution(_shell()->head);
	i = 0;
	ptr = _shell()->head;
	matrix = malloc(600);
	matrix[i++] = ft_strdup(ptr->cmd);
	// printf("matrix here %s\n", matrix[i - 1]);
	if (ptr->args)
	{
		j = 0;
		// printf("Args... \n", ptr->args[j]);
		while (ptr->args[j])
			matrix[i++] = ft_strdup((ptr->args[j++]));
	}
	matrix[i] = 0;
	path = ft_get_exec_path(matrix);
	pid = fork();
	if (pid == 0)
	{
		execve(path, matrix, _shell()->envp);
		printf("DOESNT SHOW.\n");
		exit(0);
	}
	// else if (pid < 0)
	// 	perror("minishell");
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}
}

void	minishell(void)
{
	char	*line;

	while (43)
	{
		_shell()->valid_input = true;
		line = readline("> ");
		if (ft_strlen(line) == 0)
			continue ;
		if (ft_strexact(line, "exit"))
			break ;
		add_history(line);
		add_cmds(line_to_matrix(line));
		do_execution();
		free(line);
		line = NULL;
	}
}

t_envp	init_shell(char **ev)
{
	t_envp	*shell;

	shell = _shell();
	shell->envp = ft_matrix_dup(ev, 0);
	shell->exit_code = 0;
}

void	close_shell(void)
{
	if (_shell()->head)
		free_cmds(_shell()->head);
}

int	main(int ac, char **av, char **ev)
{
	init_shell(ev);
	minishell();
	close_shell();
	return (1);
}
