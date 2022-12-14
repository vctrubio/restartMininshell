#include "../include/minishell.h"

int	ft_setenv(char *name, char *value, int overwrite)
{
	int		i;
	char	*str;

	i = -1;
	if (value == NULL)
		str = ft_strjoin(name, "=");
	else
		str = ft_concat3(name, "=", value);
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
		_shell()->envp = ft_matrix_push(_shell()->envp, ft_strdup(str));
	free(str);
	return (1);
}

int	set_cd_folder_return_if_free_folder_or_not(char **argv,
												char **ptr2folder)
{
	char	*tmp_str;
	int		to_free;

	to_free = 1;
	if (argv[1] == NULL)
		*ptr2folder = ft_getenv("HOME", 1);
	else if (argv[1][0] == '-')
		*ptr2folder = ft_getenv("OLDPWD", 1);
	else if (argv[1][0] == '~')
	{
		tmp_str = ft_getenv("HOME", 1);
		*ptr2folder = ft_strjoin(tmp_str, argv[1] + 1);
		free(tmp_str);
	}
	else
	{
		*ptr2folder = argv[1];
		to_free = 0;
	}
	return (to_free);
}

void	ft_export_no_args(void)
{
	t_vars	vars;

	ft_inicialize_vars(&vars);
	vars.matrix = ft_matrix_dup(_shell()->envp, 0);
	while (vars.matrix[vars.l] != NULL)
	{
		while (vars.matrix[vars.k + 1] != NULL)
		{
			vars.i = ft_strlen(vars.matrix[vars.k]);
			vars.j = ft_strlen(vars.matrix[vars.k + 1]);
			if (vars.i > vars.j)
				vars.i = vars.j;
			if (ft_strncmp(vars.matrix[vars.k], vars.matrix[vars.k + 1],
					vars.i) > 0)
				ft_swap2str(&(vars.matrix[vars.k]), &(vars.matrix[vars.k + 1]));
			vars.k++;
		}
		vars.k = 0;
		vars.l++;
	}
	ft_print_matrix_add_str2line_start(vars.matrix, "declare -x", " ");
	ft_matrix_free(vars.matrix);
}

int	ft_unset(char **argv)
{
	int	i;

	i = -1;
	while (_shell()->envp[++i] != NULL && ft_strncmp(_shell()->envp[i], argv[1],
			ft_strlen(argv[1])))
		;
	if (_shell()->envp[i] != NULL)
		_shell()->envp = ft_matrix_remove_col_by_index(_shell()->envp, i);
	return (0);
}
