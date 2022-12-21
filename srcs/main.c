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
			write(1, "\n", 1);
			rl_replace_line("", 0);
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

void	minishell_clean(char **line, t_cmd original_cmd)
{
	*(_shell()->head) = original_cmd;
	if (_shell()->head)
		free_cmds(_shell()->head);
	free(*line);
	*line = NULL;
}

int	readline_check(char **p2line)
{
	char	*line;

	line = *p2line;
	if (ft_strexact("''", line) || ft_strexact("\"\"", line)
		|| ft_strexact("..", line) || ft_strexact(".", line))
	{
		if (ft_strexact(".", line))
		{
			printf("bash: .: filename argument required\n");
			printf("\t.: usage: . filename [arguments]\n");
		}
		else if (ft_strexact("..", line))
			printf("bash: ..: command not found\n");
		else
			printf("bash: : command not found\n");
		free(line);
		return (1);
	}
	if (!line || line[0] == '\0' || ft_strlen(line) == 0)
	{
		if (line[0] == '\0' || ft_strlen(line) == 0)
			free(line);
		return (1);
	}
	return (0);
}

void	minishell(void)
{
	char	*line;
	t_cmd	original_cmd;

	while (!_shell()->exit)
	{
		_shell()->valid_input = true;
		line = readline("minishell.42> ");
		if (line == NULL)
			exit(0);
		if (readline_check(&line))
			continue ;
		add_history(line);
		line = ft_var_expansion(line);
		if (add_cmds(line_to_matrix(line)) && init_remove_qt())
		{
			original_cmd = *(_shell()->head);
			loop_execution(_shell()->head);
		}
		minishell_clean(&line, original_cmd);
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
