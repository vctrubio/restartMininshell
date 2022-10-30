#include "../include/minishell.h"
//parsing of envp

void	init_envp(char **envp)
{
    g_envp.envp= ft_matrix_dup(envp, 0);
	// print_arrays(g_envp.envp);
	
	// char *args[2];
    // args[0]="l";
    // args[1]=NULL;
    // ft_env(args);
}

int	ft_env(char **argv)
{
	int	i;
	int	argc;

	argc = -1;
	while (argv[++argc])
		;
	if (argc == 1)
	{
		i = -1;
		while (g_envp.envp[++i])
		{
			if (g_envp.envp[i][0] == '?' && g_envp.envp[i][1] == '=')
				continue ;
			printf("%s\n", g_envp.envp[i]);
		}
	}
	else
		printf("env: too many arguments\n");
	return (0);
}

