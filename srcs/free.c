#include "../include/minishell.h"
//free and exit functions can go here

void	free_files(t_file *first)
{
}

void	free_cmds(t_cmd *first)
{
	int i;

	if (!first)
		return ;
	while (first)
	{
		i = -1;
		if (first->cmd)
			free(first->cmd);
		while (first->args[++i])
			free(first->args[i]);
		if (first->file)
			free_files(first->file);
		if (first->next)
			first = first->next;
	}
}