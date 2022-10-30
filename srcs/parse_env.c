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
		while (_shell()->envp[++i])
		{
			if (_shell()->envp[i][0] == '?' && _shell()->envp[i][1] == '=')
				continue ;
			printf("%s\n", _shell()->envp[i]);
		}
	}
	else
		printf("env: too many arguments\n");
	return (0);
}
