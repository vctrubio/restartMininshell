#include "../include/minishell.h"

void	print_tcmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->args[++i])
		printf("ARGS[%d]= %s\n", i, cmd->args[i]);
	if (cmd->file)
		printf("FILE: %s\n", cmd->file->filename);
	printf("(%d) type\n", cmd->type);
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
