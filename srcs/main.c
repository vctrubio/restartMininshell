#include "../include/minishell.h"

void	ft_handler(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	if (signum == SIGINT)
	{
		if (pid == -1)
		{
			printf("\n");
			// rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			write(1, "\n", 1);
	}
	if (signum == SIGQUIT)
		write(1, "\n", 1);
}

int	init_remove_qt(void)
{
	t_cmd	*ptr;
	int		i;

	ptr = _shell()->head;
	while (ptr)
	{
		i = 0;
		while (ptr->args[i])
		{
			parse_clean(&(ptr->args[i]));
			i++;
		}
		ptr = ptr->next;
	}
	return (1);
}

void	minishell(void)
{
	char	*line;

	while (!_shell()->exit)
	{
		_shell()->valid_input = true;
		line = readline("minishell.42> ");
		if (line == NULL && printf("EXIT PROGRAM BUG OR CTRL+D as needed\n"))
			exit(0);
		if (!line || line[0] == '\0' || ft_strlen(line) == 0)
		{
			if (line[0] == '\0' || ft_strlen(line) == 0)
				free(line);
			continue ;
		}
		add_history(line);
		line = ft_var_expansion(line);

		// add_cmds(line_to_matrix(line));
		// print_tcmd(_shell()->head);

		if (add_cmds(line_to_matrix(line)) && init_remove_qt())
			loop_execution(_shell()->head);

		if (_shell()->head)
			free_cmds(_shell()->head);
		free(line);
		line = NULL;
	}
	free(line);
}

int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	if (ac != 1)
		return (0);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	init_shell(ev);
	minishell();
	close_shell();
	printf("exit\n");
	return (_shell()->exit_code);
}
