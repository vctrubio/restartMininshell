/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hg_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:17:04 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/27 16:00:28 by codespace        ###   ########.fr       */
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
	if (dup2(outputfd, 1) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(outputfd);
	return (outputfd);
}

int	redirect_input(t_cmd *cmd)
{
	t_file	*ptr;

	ptr = NULL;
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
		{
			if (access(ptr->filename, F_OK) == -1)
			{
				perror(ptr->filename);
				exit(1);
			}
			ptr->fd = open(ptr->filename, O_RDONLY, 0777);
		}
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

void	pipe_commands_cleanup(int num_commands, int *pipes, char *path)
{
	int	i;
	int	status;
	int	wpid;

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

void	pipe_commands_build_pipes(int *pipes, int num_commands)
{
	int	i;

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
}

void	pipe_commands_dup_n_close_pipes(t_cmd *curr, int *pipes,
		int num_commands, int i, int j)
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
}

int	run_if_first_level_builtins_set_path(t_cmd **curr, char **path,
		int *num_commands, int *i)
{
	if (*path)
		free(*path);
	if (check_if_builtin_not_pipe((*curr)))
		_shell()->exit_code = run_builtin((*curr));
	*path = ft_get_exec_path((*curr)->args);
	if (!check_if_builtin((*curr)) && !*path)
	{
		printf("bash: %s: command not found\n", ((*curr)->args)[0]);
		_shell()->exit_code = 127;
	}
	if (check_if_builtin_not_pipe((*curr)) || (!check_if_builtin((*curr))
			&& !*path))
	{
		*curr = (*curr)->next;
		*i = *i + 1;
		*num_commands = *num_commands - 1;
		return (1);
	}
	return (0);
}

void	pipe_commands_child_n_error(pid_t pid, t_cmd *curr, int *pipes,
		char *path, int *i)
{
	if (pid == 0)
	{
		pipe_commands_dup_n_close_pipes(curr, pipes, i[2], i[0], i[1]);
		if (check_if_builtin(curr))
			exit(run_builtin(curr));
		else
			exit(execve(path, curr->args, _shell()->envp));
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
}

// i[0] = i
// i[1] = j
// i[2] = num_commands
void	pipe_commands(t_cmd *cmd)
{
	int		i[3];
	int		*pipes;
	pid_t	pid;
	t_cmd	*curr;
	char	*path;

	if (cmd->args[0] == NULL)
		return ;
	path = NULL;
	i[2] = count_cmds(cmd);
	pipes = malloc(sizeof(int) * 2 * i[2]);
	pipe_commands_build_pipes(pipes, i[2]);
	curr = cmd;
	i[0] = 0;
	while (curr)
	{
		i[1] = i[0] * 2;
		if (run_if_first_level_builtins_set_path(&curr, &path, &i[2], &i[0]))
			continue ;
		pid = fork();
		pipe_commands_child_n_error(pid, curr, pipes, path, i);
		i[0]++;
		curr = curr->next;
	}
	pipe_commands_cleanup(i[2], pipes, path);
}
