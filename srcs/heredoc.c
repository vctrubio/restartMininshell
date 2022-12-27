/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:37 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/26 12:10:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ask_for_input(char *word, t_file *file)
{
	char	*line;
	char	*tmp;
	char	*filename;

	line = NULL;
	tmp = ft_strdup(".tmp.");
	file->heredoc = ft_strjoin(tmp, file->filename);
	file->fd = open(file->heredoc, O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		filename = ft_strdup(file->filename);
		ft_stradd(&filename, ">>");
		line = readline(filename);
		if (ft_strexact(line, word))
			break ;
		write(file->fd, line, ft_strlen(line));
		write(file->fd, "\n", 1);
		free(line);
		line = NULL;
		free(filename);
	}
	free(line);
	free(filename);
	free(tmp);
	close(file->fd);
}

void	init_heredoc(void)
{
	t_cmd	*cmd;

	cmd = _shell()->head;
	while (cmd != NULL)
	{
		if (cmd->file_in && (cmd->file_in->type == HEREDOC))
			ask_for_input(cmd->file_in->filename, cmd->file_in);
		cmd = cmd->next;
	}
}
