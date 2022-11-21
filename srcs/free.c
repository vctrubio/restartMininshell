#include "../include/minishell.h"
//free and exit functions can go here

void	free_files(t_file *file)
{
	free(file->filename);
	if (file->next)
		free_files(file->next);
	free(file);
}

void	free_cmds(t_cmd *first)
{
	t_cmd	*next;

	if (!first)
		return ;
	while (first)
	{
		free_arrays(first->args);
		if (first->file)
			free_files(first->file);
		if (first->file_in)
			free_files(first->file_in);
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
