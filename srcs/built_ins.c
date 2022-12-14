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

int	ft_export(char **argv)
{
	char	**name_value;
	t_vars	vars;

	ft_inicialize_vars(&vars);
	if (argv[1])
	{
		name_value = ft_strsplit(argv[1], '=');
		if (name_value[1])
			ft_setenv(name_value[0], name_value[1], 1);
		else
			ft_setenv(name_value[0], NULL, 1);
		ft_matrix_free(name_value);
		if (argv[2])
		{
			vars.i = 1;
			while (argv[++vars.i])
				printf("minishell: export \"%s\": not an identifier\n",
						argv[vars.i]);
			return (0);
		}
	}
	else
		ft_export_no_args();
	return (1);
}
