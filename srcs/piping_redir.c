#include "../include/minishell.h"

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

void	redirect_input_open(t_file *ptr)
{
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

t_file	*redirect_input_loop(t_cmd *cmd)
{
	t_file	*ptr;

	ptr = cmd->file_in;
	redirect_input_open(ptr);
	while (ptr->next)
	{
		if (ptr->type != HEREDOC)
			close(ptr->fd);
		ptr = ptr->next;
		redirect_input_open(ptr);
	}
	return (ptr);
}

int	redirect_input(t_cmd *cmd)
{
	t_file	*ptr;

	ptr = NULL;
	if (!(cmd->file_in))
		return (-1);
	if (cmd->file_in)
		ptr = redirect_input_loop(cmd);
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
	if (ptr)
		return (1);
	return (0);
}
