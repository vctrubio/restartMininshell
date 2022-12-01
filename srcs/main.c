#include "../include/minishell.h"

void	init_remove_qt(void)
{
	t_cmd 	*ptr;
	int		i = 0;

	ptr = _shell()->head;
	while (ptr)
	{
		i = 0;
		while (ptr->args[i])
		{
			printf("PARSE CLEAN= %s\n", parse_clean(ptr->args[i]));
			i++;
		}
		ptr = ptr->next;
	}
}

void	minishell(void)
{
	char	*line;

	while (43)
	{
		_shell()->valid_input = true;
		line = readline("minishell.42> ");
		if (line == NULL)
		{
			printf("EXIT PROGRAM BUG\n");
			exit(0);
		}
		if (!line || line[0] == '\0')
			continue ;
		if (ft_strlen(line) == 0)
			continue ;
		if (ft_strexact(line, "exit"))
			break ;
		add_history(line);
		line = ft_var_expansion(line);
		if (add_cmds(line_to_matrix(line)))
		{
			init_remove_qt();
			loop_execution(_shell()->head);
		}
		// printf("\n--ARGS INPUT--\n");
		// if (_shell()->head)
		// 	print_tcmd(_shell()->head);
		// if (_shell()->head)
		// 	free_cmds(_shell()->head);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
}

int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	if (ac != 1)
		return (0);
	init_shell(ev);
	minishell();
	close_shell();
	return (1); //need to return EXIT_CODE?¿
}
