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
