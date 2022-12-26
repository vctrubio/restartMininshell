/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hg_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:17:04 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/26 12:19:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	redirect_output(t_cmd *cmd)
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

int	redirect_input(t_cmd *cmd)
{
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
	char	*path;
	int		ret;
	int		status;
	pid_t	wpid;
	int		i;
	int		j;

	path = NULL;
	num_commands = count_cmds(cmd);
	pipes = malloc(sizeof(int) * 2 * num_commands);
	if (pipes == NULL)
	{
		perror("malloc");
		exit(1);
	}
	i = 0;
	while (i < num_commands)
	{
		if (pipe(pipes + i * 2) < 0)
		{
			perror("pipe");
			exit(1);
		}
		i++;
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
			num_commands--;
			continue ;
		}
		pid = fork();
		if (pid == 0)
		{
			redirect_input(curr);
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
			i = 0;
			while (i < 2 * num_commands)
			{
				close(pipes[i]);
				i++;
			}
			redirect_output(curr);
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
	i = 0;
	while (i < 2 * num_commands)
	{
		close(pipes[i]);
		i++;
	}
	i = 0;
	while (i < num_commands)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid < 0)
		{
			//perror("waitpid");
			//exit(1);
		}
		_shell()->exit_code = status / 256;
		i++;
	}
	if (path)
		free(path);
	free(pipes);
}
