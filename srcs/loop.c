/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:17:04 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/12/26 11:50:06 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	loop_part1(t_cmd **cmd, char **path)
{
	*path = NULL;
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

void	loop_parent(t_cmd **p2cmd, int *pid, int *p)
{
	t_cmd	*cmd;
	int		status;

	cmd = *p2cmd;
	waitpid(*pid, &status, WUNTRACED);
	if (cmd->next)
		cmd->next->fd_in = dup(p[0]);
	close(p[1]);
	close(p[0]);
	*p2cmd = (*p2cmd)->next;
	_shell()->exit_code = status / 256;
}

void	loop_execution(t_cmd *cmd)
{
	int		p[2];
	pid_t	pid;
	char	*path;

	printf("printing loop...\n");
	print_tcmd(_shell()->head);
	while (cmd && cmd->args[0])
	{
		if (loop_part1(&cmd, &path))
			continue ;
		if (cmd && cmd->prev == NULL)
			cmd->fd_in = p[0];
		pipe(p);
		pid = fork();
		if (pid == 0)
			loop_child(cmd, p, path);
		else
		{
			loop_parent(&cmd, &pid, p);
			if (path)
				free(path);
		}
	}
}
