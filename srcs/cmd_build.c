#include "../include/minishell.h"
//this is where it gets interesting

void	build_struct(char *cmd)
{

	printf("ft_build_struct\n");
	while(*cmd)
	{
		printf("%s--\n", *cmd);
		(cmd)++;
	}
}


void	build_cmds(char **cmds)
{
	printf("ft_build_cmds\n");
	while (*cmds)
	{
		build_struct(*cmds);
	}
}