/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:28 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/25 14:34:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_redir_back(t_cmd *cmd, char ****str)
{
	if (ft_strexact(***str, "<"))
	{
		cmd->type = R_IN;
		**(str) = **str + 1;
		create_infile(***str, cmd);
	}
	else if (ft_strexact(***str, "<<"))
	{
		cmd->type = HEREDOC;
		**(str) = **str + 1;
		create_infile(***str, cmd);
	}
}

void	set_redir(t_cmd *cmd, char ****str)
{
	if (ft_strexact(***str, ">"))
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