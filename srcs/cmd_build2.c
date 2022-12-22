/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrubio < vrubio@student.42lisboa.com >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:25:40 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/22 11:25:41 by vrubio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_redir_back(t_cmd *cmd, char ****str)
{
	if (ft_strexact(***str, "<"))
	{
		**(str) = **str + 1;
		create_infile(***str, cmd);
	}
	else if (ft_strexact(***str, "<<"))
	{
		cmd->type = HEREDOC;
		**(str) = **str + 1;
		create_heredoc(***str, cmd);
	}
}

void	set_redir(t_cmd *cmd, char ****str)
{
	if (ft_strexact(***str, "|"))
		;
	else if (ft_strexact(***str, ">"))
	{
		cmd->type = R_OUT;
		**(str) = **str + 1;
		create_file(***str, cmd);
	}
	else if (ft_strexact(***str, ">>"))
	{
		cmd->type = R_APP;
		**(str) = **str + 1;
		create_file(***str, cmd);
	}
	set_redir_back(cmd, str);
	**(str) = **str + 1;
	if (***str && is_redir(****str))
		set_redir(cmd, str);
}

void	create_heredoc(char *str, t_cmd *cmd)
{
	t_file	*file;
	t_file	*ptr;

	file = malloc(sizeof(t_file));
	file->filename = ft_strdup(str);
	file->type = HEREDOC;
	file->next = NULL;
	if (cmd->heredoc)
	{
		ptr = cmd->heredoc;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = file;
	}
	else
		cmd->heredoc = file;
}
