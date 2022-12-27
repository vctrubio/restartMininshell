/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:27 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/27 16:21:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_n_clean_file(t_file *file)
{
	file->fd = open(file->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(file->fd);
	free_files(file);
}

void	create_file(char *str, t_cmd *cmd)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	file->filename = ft_strdup(str);
	file->type = cmd->type;
	file->heredoc = NULL;
	file->next = NULL;
	if (cmd->file)
		create_n_clean_file(cmd->file);
	cmd->file = file;
}

void	create_infile(char *str, t_cmd *cmd)
{
	t_file	*file;
	t_file	*ptr;
	
	file = malloc(sizeof(t_file));
	file->filename = ft_strdup(str);
	file->heredoc = NULL;
	file->next = NULL;
	file->type = cmd->type;
	if (cmd->file_in)
	{
		ptr = cmd->file_in;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = file;
	}
	else
		cmd->file_in = file;
}

t_cmd	*init_tcmd(char ***matrix, int i)
{
	t_cmd	*cmd;

	cmd = ft_inicialize_cmd(*matrix);
	while (**matrix != NULL)
	{
		if (!is_redir(***matrix))
		{
			if (ft_strexact("cat", **matrix))
				cmd->flag = 1;
			cmd->args[i++] = ft_strdup((**matrix));
		}
		else if (ft_strexact(**matrix, "|"))
		{
			*(matrix) = *matrix + 1;
			break;
		}	
		else
		{
			set_redir(cmd, &matrix);
			if (**matrix && !ft_strexact(**matrix, "|"))
				continue ;
		}
		if (**matrix)
			*(matrix) = *matrix + 1;
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
	validate_rl(matrix);
	if (_shell()->valid_input == false)
	{
		printf("ERROR: SYNTAX ERROR...\n");
		return (false);
	}
	else
		build_cmds(matrix);
	init_heredoc();
	return (true);
}
