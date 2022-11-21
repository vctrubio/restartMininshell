#include "../include/minishell.h"
//free and exit functions can go here

void	free_files(t_cmd *first)
{
	// printf("freeeeeee files called\n");
}

void	free_cmds(t_cmd *first)
{
	int		i;
	t_cmd	*next;

	if (!first)
		return ;
	while (first)
	{
		i = -1;
		while (first->args[++i])
			free(first->args[i]);
		free(first->args);
		if (first->file)
			free_files(first);
		// if (first->pipe)
		// 	free_pipe(first->pipe);
		if (first->next)
			next = first->next;
		else
			break ;
		free(first);
		first = next;
	}
	if (first)
		free(first);
}
