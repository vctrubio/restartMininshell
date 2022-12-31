/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_checkers_n_runners.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrubio < vrubio@student.42lisboa.com >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:24 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/22 15:19:25 by vrubio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_if_builtin(t_cmd *cmd)
{
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

int	run_builtin(t_cmd *cmd)
{
	int	ret;

	if (ft_strexact("pwd", cmd->args[0]))
		ret = ft_pwd(cmd->args);
	if (ft_strexact("echo", cmd->args[0]))
		ret = ft_echo(cmd->args);
	if (ft_strexact("env", cmd->args[0]))
		ret = ft_env(cmd->args);
	if (ft_strexact("cd", cmd->args[0]))
		ret = ft_cd(cmd->args);
	if (ft_strexact("export", cmd->args[0]))
		ret = ft_export(cmd->args);
	if (ft_strexact("unset", cmd->args[0]) && cmd->args[1])
		ret = ft_unset(cmd->args);
	if (ft_strexact("exit", cmd->args[0]))
		ret = ft_exit(cmd->args);
	_shell()->exit_code = ret;
	return (ret);
}

int	check_if_builtin_not_pipe(t_cmd *cmd)
{
	if (!cmd->next)
	{
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

int	run_builtin_not_piped(t_cmd *cmd)
{
	int	ret;

	if (ft_strexact("cd", cmd->args[0]))
		ret = ft_cd(cmd->args);
	if (ft_strexact("export", cmd->args[0]))
		ret = ft_export(cmd->args);
	if (ft_strexact("unset", cmd->args[0]) && cmd->args[1])
		ret = ft_unset(cmd->args);
	if (ft_strexact("exit", cmd->args[0]))
		ret = ft_exit(cmd->args);
	return (ret);
}

int	run_builtin_2pipe(t_cmd *cmd)
{
	int	ret;

	if (ft_strexact("pwd", cmd->args[0]))
		ret = ft_pwd(cmd->args);
	if (ft_strexact("echo", cmd->args[0]))
		ret = ft_echo(cmd->args);
	if (ft_strexact("env", cmd->args[0]))
		ret = ft_env(cmd->args);
	_shell()->exit_code = ret;
	return (ret);
}
