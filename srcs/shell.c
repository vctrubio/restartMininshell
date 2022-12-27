/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:20:05 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/27 15:55:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_envp	*_shell(void)
{
	static t_envp	enviroment;

	return (&enviroment);
}

void	init_shell(char **ev)
{
	t_envp	*shell;

	shell = _shell();
	shell->envp = ft_matrix_dup(ev, 0);
	shell->exit_code = 0;
	shell->exit = 0;
}

void	close_shell(void)
{
	if (_shell()->head)
		free_cmds(_shell()->head);
	if (_shell()->envp)
		free_arrays(_shell()->envp);
}
