#include "../include/minishell.h"

static int	free_heredoc(t_file *file)
{
	free(file->filename);
	if (file->heredoc)
	{
		remove(file->heredoc);
		free(file->heredoc);
	}
	if (file->next)
		free_heredoc(file->next);
	free(file);
	return (1);
}

static int	free_files(t_file *file)
{
	if (file->next)
		free_files(file->next);
	free(file->filename);
	free(file);
	return (1);
}

void	free_cmds(t_cmd *first)
{
	t_cmd	*next;

	if (!first)
		return ;
	while (first)
	{
		free_arrays(first->args);
		if (first->file && free_files(first->file))
			first->file = NULL;
		if (first->file_in && free_files(first->file_in))
			first->file_in = NULL;
		if (first->heredoc && free_heredoc(first->heredoc))
			first->heredoc = NULL;
		if (first->next)
			next = first->next;
		else
			break ;
		free(first);
		first = next;
	}
	if (first)
		free(first);
	_shell()->head = NULL;
}
