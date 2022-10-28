#include "../include/minishell.h"

t_envp	g_envp;

void	add_cmds(char **cmds)
{
	validate_rl(cmds);
	if (g_envp.valid_input == false)
		printf("INVALID USER INPUT... ERROR IN PARSING... TBD\n");

	// print_arrays(cmds);
	build_cmds(cmds);
	free_arrays(cmds);
}

void	minishell(void)
{
	char	*line;
	while (43)
	{
		g_envp.valid_input = true;
		line = readline("> ");
		if (ft_strlen(line) == 0)
			continue;
		if (ft_strexact(line, "exit")) //it doesnt have to be exact but you get the point
			break;
		add_history(line);
		add_cmds(line_to_arrays(line));
		free(line);
		line = NULL;
	}
}

int main(int ac, char **av, char **ev)
{
	printf("ft_main_minishell\n");
	g_envp.exit_code = 0;
	minishell();
	return (g_envp.exit_code);
}



