/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:27 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/29 20:19:52 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// -1 =break
// 1 = continue
// 0= do nothing
int	init_tcmd_while(char ***matrix, int *i, t_cmd **cmd)
{
	if (!is_redir(***matrix) && !ft_strexact(**matrix, "|"))
		(*cmd)->args[(*i)++] = ft_strdup((**matrix));
	else if (ft_strexact(**matrix, "|"))
	{
		*(matrix) = *matrix + 1;
		return (-1);
	}
	else
	{
		set_redir(*cmd, &matrix);
		if (**matrix && !ft_strexact(**matrix, "|"))
			return (1);
	}
	if (**matrix && !ft_strexact(**matrix, "|"))
		*(matrix) = *matrix + 1;
	return (0);
}

t_cmd	*init_tcmd(char ***matrix, int i)
{
	t_cmd	*cmd;
	int		loop_ret;

	cmd = ft_inicialize_cmd(*matrix);
	while (**matrix != NULL)
	{
		loop_ret = init_tcmd_while(matrix, &i, &cmd);
		if (loop_ret == -1)
			break ;
		else if (loop_ret == 1)
			continue ;
	}
	cmd->args[i] = NULL;
	return (cmd);
}

void	build_cmds(char **matrix)
{
	t_cmd	*ptr;
	t_cmd	*ptr_next;
	char	**ptr_to_free;

	ptr_to_free = matrix;
	ptr = init_tcmd(&matrix, 0);
	_shell()->head = ptr;
	while (*matrix != NULL)
	{
		ptr_next = init_tcmd(&matrix, 0);
		ptr->next = ptr_next;
		ptr_next->prev = ptr;
		ptr = ptr->next;
	}
	free_arrays(ptr_to_free);
}

bool	add_cmds(char **matrix)
{
	// print_arrays(matrix);
	validate_rl(matrix);
	if (_shell()->valid_input == false)
	{
		printf("\033[0;31msyntax error near unexpected token `newline'\033[0m\n");
		return (false);
	}
	else
		build_cmds(matrix);
	init_heredoc();
	return (true);
}
