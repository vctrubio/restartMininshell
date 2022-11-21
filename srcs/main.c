#include "../include/minishell.h"

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
		if (add_cmds(line_to_matrix(line)))
			loop_execution(_shell()->head);
		free_cmds(_shell()->head);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
}

int	main(int ac, char **av, char **ev)
{
	init_shell(ev);
	minishell();
	close_shell();
	return (1);
}
