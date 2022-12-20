#include "../include/minishell.h"

void	loop_remove_zsh(t_cmd *cmd)
{
	while (cmd->file && cmd->file->next)
	{
		cmd->file->fd = open(cmd->file->filename, O_WRONLY | O_CREAT | O_TRUNC,
				0777);
		close(cmd->file->fd);
		cmd->file = cmd->file->next;
	}
	while (cmd->file_in && cmd->file_in->next)
		cmd->file_in = cmd->file_in->next;
}

int	does_next_read_stdi(t_cmd *cmd)
{
	if (ft_strexact("w", (cmd->next)->args[0]) || ft_strexact("ls",
			(cmd->next)->args[0]) || ft_strexact("pwd", (cmd->next)->args[0]))
		return (1);
	return (0);
}

void	setup_catbs(t_cmd **p2cmd)
{
	t_cmd	*cmd;

	cmd = *p2cmd;
	if (cmd->flag && cmd->next && cmd->next->next)
	{
		if (cmd->args[1] == NULL && ft_strexact("cat", cmd->args[0])
			&& ft_strexact("cat", (cmd->next)->args[0])
			&& !does_next_read_stdi(cmd->next))
			*p2cmd = cmd->next;
	}
	if (cmd->flag && cmd->next)
	{
		if (does_next_read_stdi(cmd) && cmd->args[1] == NULL && !cmd->file_in
			&& !cmd->file && !cmd->heredoc)
			cmd->flag = 2;
		if (cmd->args[1] == NULL && !cmd->file_in && !cmd->file && !cmd->heredoc
			&& (ft_strexact("cat", (cmd->next)->args[0])))
			cmd->flag = 2;
	}
}

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

	child_proces(p, cmd);
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
	else
		waitpid(*pid, &status_bs[0], WUNTRACED);
	close(p[1]);
	loop_files(&cmd);
	*p2cmd = (*p2cmd)->next;
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
	bs_cat(status_bs[1]);
}
