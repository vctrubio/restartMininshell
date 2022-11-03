#include "../include/minishell.h"
//free and exit functions can go here

void	free_files(t_file *first)
{
	free(first->filename);
	free(first);
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
			free_files(first->file);
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
