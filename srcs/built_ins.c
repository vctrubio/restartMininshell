#include "../include/minishell.h"

int	ft_cd(char **argv)
{
	char	*folder;
	int		to_free;
	char	pwd[256];
	int		ret;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("getcwd() error");
	to_free = set_cd_folder_return_if_free_folder_or_not(argv, &folder);
	ret = chdir(folder);
	if (ret != 0)
		perror("minishell");
	ft_setenv("OLDPWD", pwd, 1);
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("getcwd() error");
	ft_setenv("PWD", pwd, 1);
	if (to_free)
		free(folder);
	return (ret * (-1));
}

int	ft_echo(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL && ft_strncmp(argv[i], "-n", 2) == 0)
		i++;
	while (argv[i] != NULL)
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (argv[1] == NULL || ft_strncmp(argv[1], "-n", 2) != 0
		|| (ft_strncmp(argv[1], "-n", 2) == 0 && argv[1][2]
			&& !ft_isalpha(argv[1][2])))
		ft_putchar_fd('\n', 1);
	return (0);
}

int	ft_pwd(char **argv)
{
	char	cwd[256];

	(void)argv;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	else
		printf("%s\n", cwd);
	return (0);
}

void	ft_export_loop(char **argv)
{
	char	**name_value;
	char	*tmpstr;

	name_value = ft_strsplit(*argv, '=');
	if (name_value[1])
	{
		printf("--%s\n",name_value[1]);
		tmpstr = ft_concat_multi(name_value+1,"=");
		ft_setenv(name_value[0], tmpstr, 1);
		free(tmpstr);
	}
	else
		ft_setenv(name_value[0], NULL, 1);
	ft_matrix_free(name_value);	
}

int	ft_export(char **argv)
{
	if (*argv && ft_strlen(*argv) == 0)
		return (0);
	argv++;
	if (*argv)
	{
		while (*argv != NULL)
		{
			ft_export_loop(argv);
			argv++;
		}
	}
	else
		ft_export_no_args();
	return (1);
}

int	ft_setenv(char *name, char *value, int overwrite)
{
	int		i;
	char	*str;
	char	**envp;

	i = -1;
	str = NULL;
	str = ft_setenv_str(name, value, str);
	if (str == NULL)
		return (0);
	while (_shell()->envp[++i] != NULL && name && ft_strncmp(_shell()->envp[i],
			name, ft_strlen(name)))
		;
	if (_shell()->envp[i] != NULL && overwrite == 1)
	{
		free(_shell()->envp[i]);
		_shell()->envp[i] = ft_strdup(str);
	}
	else if (_shell()->envp[i] == NULL)
	{
		envp = ft_matrix_push(_shell()->envp, ft_strdup(str));
		_shell()->envp = envp;
	}
	free(str);
	return (1);
}
