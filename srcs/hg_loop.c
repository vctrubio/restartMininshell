/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:17:04 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/25 17:35:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_process_end(int *p, t_cmd *cmd, t_file *ptr)
{
	if (cmd->file && cmd->file->type == R_OUT)
	{
		ptr = cmd->file;
		ptr->fd = open(ptr->filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(ptr->fd, 1);
	}
	else if (cmd->file && cmd->file->type == R_APP)
	{
		ptr = cmd->file;
		ptr->fd = open(ptr->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
		dup2(ptr->fd, 1);
	}
	else if (cmd->next)
		dup2(p[1], 1);
}

int	child_proces(int *p, t_cmd *cmd)
{
	t_file	*ptr;

	if (cmd->file_in)
	{
		ptr = cmd->file_in;
		if (ptr->type == HEREDOC)
			ptr->fd = open(ptr->heredoc, O_RDONLY, 0777);
		else
			ptr->fd = open(ptr->filename, O_RDONLY, 0777);
		if (ptr->fd < 0)
			return (1);
		cmd->fd_in = ptr->fd;
	}
	dup2(cmd->fd_in, 0);
	child_process_end(p, cmd, ptr);
	close(p[0]);
	if (cmd->next == NULL)
		close(p[1]);
	return (0);
}


int	count_cmds(t_cmd *cmd)
{
	int		i;
	t_cmd	*curr;

	i = 0;
	curr = cmd;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

int	redirectOutput(t_cmd *cmd)
{
	int		outputfd;
	t_file	*file;

	if (!(cmd->file && (cmd->file->type == R_OUT || cmd->file->type == R_APP)))
	{
		return (-1);
	}
	file = cmd->file;
	if (file->type == R_OUT)
		outputfd = open(file->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		outputfd = open(file->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outputfd < 0)
	{
		perror("open");
		exit(1);
	}
	if (dup2(outputfd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(outputfd);
	return (0);
}

int	redirectInput(t_cmd *cmd)
{
	int		inputfd;
	t_file	*ptr;

	if (!(cmd->file_in))
	{
		return (-1);
	}
	if (cmd->file_in)
	{
		ptr = cmd->file_in;
		if (ptr->type == HEREDOC)
			ptr->fd = open(ptr->heredoc, O_RDONLY, 0777);
		else
			ptr->fd = open(ptr->filename, O_RDONLY, 0777);
		if (ptr->fd < 0)
			return (1);
		cmd->fd_in = ptr->fd;
	}
	if (ptr->fd < 0)
	{
		perror("open");
		exit(1);
	}
	cmd->fd_in = ptr->fd;
	if (dup2(ptr->fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(ptr->fd);
	return (0);
}

void	pipe_commands(t_cmd *cmd)
{
	int		num_commands;
	int		*pipes;
	pid_t	pid;
	t_cmd	*curr;
	char	*command_str;
	int		arg_index;
	char	*path;
	int		ret;
	int		status;
	pid_t	wpid;

	path = NULL;
	num_commands = count_cmds(cmd);
	pipes = malloc(sizeof(int) * 2 * num_commands);
	if (pipes == NULL)
	{
		perror("malloc");
		exit(1);
	}
	int i, j;
	for (i = 0; i < num_commands; i++)
	{
		if (pipe(pipes + i * 2) < 0)
		{
			perror("pipe");
			exit(1);
		}
	}
	curr = cmd;
	i = 0;
	while (curr)
	{
		j = i * 2;
		if (path)
			free(path);
		if (loop_part1(&curr, &path))
		{
			i++;
			continue ;
		}
		pid = fork();
		if (pid == 0)
		{
			redirectInput(curr);
			if (i > 0)
			{
				if (dup2(pipes[j - 2], STDIN_FILENO) < 0)
				{
					perror("dup2");
					exit(1);
				}
			}
			if (i < num_commands - 1)
			{
				if (dup2(pipes[j + 1], STDOUT_FILENO) < 0)
				{
					perror("dup2");
					exit(1);
				}
			}
			for (int k = 0; k < 2 * num_commands; k++)
			{
				close(pipes[k]);
			}
			redirectOutput(curr);
			if (check_if_builtin_2pipe(cmd))
				ret = run_builtin_2pipe(cmd);
			else
				ret = execve(path, cmd->args, _shell()->envp);
			exit(ret);
		}
		else if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
		i++;
		curr = curr->next;
	}
	for (i = 0; i < 2 * num_commands; i++)
	{
		close(pipes[i]);
	}
	for (i = 0; i < num_commands; i++)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid < 0)
		{
			//perror("waitpid");
			exit(1);
		}
	}
	_shell()->exit_code = status / 256;
	if (path)
		free(path);
	free(pipes);
}
