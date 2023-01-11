/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_checkers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:24 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/12/29 19:59:27 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_if_builtin(t_cmd *cmd)
{
	if (ft_strchr(cmd->args[0], '='))
		return (1);
	if (ft_strexact("cd", cmd->args[0]))
		return (1);
	if (ft_strexact("export", cmd->args[0]))
		return (1);
	if (ft_strexact("unset", cmd->args[0]))
		return (1);
	if (ft_strexact("exit", cmd->args[0]))
		return (1);
	if (ft_strexact("pwd", cmd->args[0]))
		return (1);
	if (ft_strexact("echo", cmd->args[0]))
		return (1);
	if (ft_strexact("env", cmd->args[0]))
		return (1);
	return (0);
}

int	check_if_builtin_not_pipe(t_cmd *cmd)
{
	if (!cmd->next)
	{
		if (ft_strchr(cmd->args[0], '='))
			return (1);
		if (ft_strexact("cd", cmd->args[0]))
			return (1);
		if (ft_strexact("export", cmd->args[0]))
			return (1);
		if (ft_strexact("unset", cmd->args[0]))
			return (1);
		if (ft_strexact("exit", cmd->args[0]))
			return (1);
	}
	return (0);
}

int	check_if_builtin_2pipe(t_cmd *cmd)
{
	if (ft_strexact("pwd", cmd->args[0]))
		return (1);
	if (ft_strexact("echo", cmd->args[0]))
		return (1);
	if (ft_strexact("env", cmd->args[0]))
		return (1);
	return (0);
}
