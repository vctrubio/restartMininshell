#include "../include/minishell.h"

int	check_if_builtin_not_pipe(t_cmd *cmd)
{
	if (ft_strexact("cd", cmd->args[0]))
		return (1);
	if (ft_strexact("export", cmd->args[0]))
		return (1);
	if (ft_strexact("unset", cmd->args[0]))
		return (1);
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
	if (ft_strexact("unset", cmd->args[0]))
		ret = ft_unset(cmd->args);
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