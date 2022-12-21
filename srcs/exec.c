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
		ptr->fd = open(ptr->filename, O_RDONLY, 0777);
		if (ptr->fd < 0)
			return (1);
		cmd->fd_in = ptr->fd;
	}
	if (cmd->heredoc)
	{
		ptr = cmd->heredoc;
		ptr->fd = open(ptr->heredoc, O_RDONLY, 0777);
		if (ptr->fd < 0)
			return (1);
		cmd->fd_in = ptr->fd;
	}
	dup2(cmd->fd_in, 0);
	child_process_end(p, cmd, ptr);
	if (cmd->flag != 2)
		close(cmd->fd_in);
	close(p[0]);
	return (0);
}

void	bs_cat(int bs_cat)
{
	char	*tmpstr;

	while (bs_cat--)
	{
		tmpstr = readline("");
		printf("\n");
		free(tmpstr);
	}
}
