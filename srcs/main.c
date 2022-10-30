#include "../include/minishell.h"

void	add_cmds(char **matrix)
{
	validate_rl(matrix);
	if (_shell()->valid_input == false)
		printf("INVALID USER INPUT... ERROR IN PARSING... TBD\n");
	build_cmds(matrix);
	// free_arrays(matrix);
}

void	do_execution(void)
{
	t_cmd	*ptr;
	char	**matrix;
	int		i;
	int		j;

	i = 0;
	ptr = _shell()->head;
	matrix[i++] = ptr->cmd;
	if (ptr->args)
	{
		j = 0;
		while (ptr->args[j])
			matrix[i++] = (ptr->args[j++]);
	}
	matrix[i] = 0;
	// print_arrays(matrix);
	printf("\nPATH=%s\n", ft_get_exec_path(matrix));
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
