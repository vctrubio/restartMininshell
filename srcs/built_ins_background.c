/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_background.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrubio < vrubio@student.42lisboa.com >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:22 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/22 15:19:23 by vrubio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_setenv_str(char *name, char *value, char *str)
{
	if (value == NULL)
		str = ft_strjoin(name, "=");
	else
		str = ft_concat3(name, "=", value);
	return (str);
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

void	unset_loop(char *argv)
{
	int		i;
	char	**envp;

	envp = NULL;
	i = -1;
	while (_shell()->envp[++i] != NULL && *argv && ft_strncmp(_shell()->envp[i], argv,
		ft_strlen(argv)))
		;
	if (_shell()->envp[i] != NULL)
	{
		envp = ft_matrix_remove_col_by_index(_shell()->envp, i);
		_shell()->envp = envp;
	}
}

int	ft_unset(char **argv)
{
	argv++;
	if (*argv)
	{
		while (*argv)
		{
			unset_loop(*argv);
			argv++;
		}
	}
	return (0);
}

int	ft_exit(char **argv)
{
	if (argv[1])
	{
		_shell()->exit_code = ft_atoi(argv[1]);
		return (ft_atoi(argv[1]));
	}
	else
	{
		_shell()->exit_code = 0;
		return (0);
	}
}
