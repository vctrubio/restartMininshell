/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:36 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/25 18:06:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	free_files(t_file *file)
{
	if (file->next)
		free_files(file->next);
	free(file->filename);
	if (file->heredoc)
	{
		remove(file->heredoc);
		free(file->heredoc);
	}
	free(file);
	return (1);
}

void	free_cmds(t_cmd *first)
{
	t_cmd	*next;

	if (!first)
		return ;
	while (first)
	{
		free_arrays(first->args);
		if (first->file && free_files(first->file))
			first->file = NULL;
		if (first->file_in && free_files(first->file_in))
			first->file_in = NULL;
		if (first->next)
			next = first->next;
		else
			break ;
		free(first);
		first = next;
	}
	if (first)
		free(first);
	_shell()->head = NULL;
}

void	minishell_clean(char **line, t_cmd original_cmd)
{
	if (original_cmd.args)
		*(_shell()->head) = original_cmd;
	if (_shell()->head)
		free_cmds(_shell()->head);
	free(*line);
	*line = NULL;
}
