#include "../include/minishell.h"
//parsing of envp

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

