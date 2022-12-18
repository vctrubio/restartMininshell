#include "../include/minishell.h"

void	print_tcmd(t_cmd *cmd)
{
	int		i;
	t_file	*file;

	file = NULL;
	i = -1;
	while (cmd->args[++i])
		printf("ARGS[%d]= %s\n", i, cmd->args[i]);
	if (cmd->file)
	{
		file = cmd->file;
		while (file)
		{
			printf("FILE_OUT: %s (%d)\n", file->filename, file->type);
			file = file->next;
		}
	}
	if (cmd->heredoc)
	{
		printf("FILE HEREDOC: %s (%d)\n", cmd->heredoc->filename,
				cmd->heredoc->type);
	}
	if (cmd->file_in)
	{
		file = cmd->file_in;
		while (file)
		{
			printf("FILE_IN: %s (%d)\n", file->filename,
				file->type);
			file = file->next;
		}
	}
	printf("(%d) type__________\n", cmd->type);
	if (cmd->next)
		print_tcmd(cmd->next);
}

void	free_arrays(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i++] = NULL;
	}
	free(arr);
	arr = NULL;
}

void	print_arrays(char **a)
{
	int	i;

	i = -1;
	while (a[++i])
		printf("[%d] %s\n", i, a[i]);
}
