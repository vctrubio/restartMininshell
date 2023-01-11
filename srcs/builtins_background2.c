/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_background2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:50:19 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/12/29 19:50:21 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit(char **argv)
{
	if (argv[1])
	{
		_shell()->exit_code = ft_atoi(argv[1]);
		_shell()->exit = 1;
		return (ft_atoi(argv[1]));
	}
	else
	{
		_shell()->exit_code = 0;
		_shell()->exit = 1;
		return (0);
	}
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
