/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:58 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/12/27 15:55:16 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
