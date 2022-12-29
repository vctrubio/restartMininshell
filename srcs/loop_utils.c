/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:40 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/12/29 20:03:08 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			&& !cmd->file)
			cmd->flag = 2;
		if (cmd->args[1] == NULL && !cmd->file_in && !cmd->file
			&& (ft_strexact("cat", (cmd->next)->args[0])))
			cmd->flag = 2;
	}
}
