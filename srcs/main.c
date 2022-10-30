#include "../include/minishell.h"

t_envp	g_envp;

void	add_cmds(char **matrix)
{
	validate_rl(matrix);
	if (g_envp.valid_input == false)
		printf("INVALID USER INPUT... ERROR IN PARSING... TBD\n");

	// print_arrays(matrix);
	build_cmds(matrix);
	// free_matrix(matrix);
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
		add_cmds(line_to_matrix(line));
		free(line);
		line = NULL;
		//Where do we free the matrix
	}
}

int main(int ac, char **av, char **ev)
{
	printf("ft_main_minishell\n");
	init_envp(ev);
	g_envp.exit_code = 0;
	minishell();
	return (g_envp.exit_code);
}



