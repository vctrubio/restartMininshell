/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:27 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/29 20:04:44 by hgoncalv         ###   ########.fr       */
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
