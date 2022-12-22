/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrubio < vrubio@student.42lisboa.com >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:16:21 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/22 11:23:45 by vrubio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	loop_part1(t_cmd **cmd, char **path)
{
	setup_catbs(cmd);
	*path = NULL;
	loop_remove_zsh(*cmd);
	if (check_if_builtin_not_pipe(*cmd))
	{
		_shell()->exit_code = run_builtin_not_piped(*cmd);
		if (!((*cmd)->next) && !((*cmd)->prev) && ft_strexact("exit",
				(*cmd)->args[0]))
			_shell()->exit = 1;
		*cmd = (*cmd)->next;
		return (1);
	}
	if (!check_if_builtin_2pipe(*cmd))
		*path = ft_get_exec_path((*cmd)->args);
	if (!check_if_builtin_2pipe(*cmd) && !(*path))
	{
		printf("bash: %s: command not found\n", *((*cmd)->args));
		_shell()->exit_code = 127;
		*cmd = (*cmd)->next;
		return (1);
	}
	return (0);
}

void	loop_files(t_cmd **cmd)
{
	if ((*cmd)->file && (*cmd)->file->next)
	{
		(*cmd)->file = (*cmd)->file->next;
		loop_execution(*cmd);
	}
	if ((*cmd)->file_in && (*cmd)->file_in->next)
	{
		(*cmd)->file_in = (*cmd)->file_in->next;
		loop_execution(*cmd);
	}
	if ((*cmd)->heredoc && (*cmd)->heredoc->next)
	{
		(*cmd)->heredoc = (*cmd)->heredoc->next;
		loop_execution(*cmd);
	}
}

void	loop_child(t_cmd *cmd, int *p, char *path)
{
	int	ret;

	if (child_proces(p, cmd) == 1)
	{
		perror((cmd->args)[0]);
		exit(1);
	}
	if (check_if_builtin_2pipe(cmd))
		ret = run_builtin_2pipe(cmd);
	else
		ret = execve(path, cmd->args, _shell()->envp);
	exit(ret);
}

void	loop_parent(t_cmd **p2cmd, int *pid, int *p, int *status_bs)
{
	t_cmd	*cmd;

	cmd = *p2cmd;
	if (cmd->flag == 2 && ++(status_bs[1]))
		kill(*pid, SIGKILL);
	// else
	// 	waitpid(*pid, &status_bs[0], WUNTRACED);
	close(p[1]);
	loop_files(&cmd);
	*p2cmd = (*p2cmd)->next;== 2 
	_shell()->exit_code = status_bs[0] / 256;
}

void	loop_execution(t_cmd *cmd)
{
	int		p[2];
	pid_t	pid;
	int		status_bs[2];
	char	*path;

	status_bs[1] = 0;
	while (cmd && cmd->args[0])
	{
		if (loop_part1(&cmd, &path))
			continue ;
		if (cmd)
			cmd->fd_in = p[0];
		pipe(p);
		pid = fork();
		if (pid == 0)
			loop_child(cmd, p, path);
		else
		{
			loop_parent(&cmd, &pid, p, status_bs);
			if (path)
				free(path);
		}
	}
	// if (cmd->flag && ++(status_bs[1]))
	// 	kill(pid, SIGKILL);
	// else
	waitpid(pid, &status_bs[0], WUNTRACED);
	bs_cat(status_bs[1]);
}
