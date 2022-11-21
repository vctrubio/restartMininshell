#include "../include/minishell.h"

void	print_tcmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->args[++i])
		printf("ARGS[%d]= %s\n", i, cmd->args[i]);
	if (cmd->file)
	{
		while (cmd->file)
		{
			printf("FILE_OUT: %s (%d)\n", cmd->file->filename, cmd->file->type);
			cmd->file = cmd->file->next;
		}
	}
	if (cmd->file_in)
		printf("FILE_IN: %s (%d)\n", cmd->file_in->filename, cmd->file_in->type);
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
