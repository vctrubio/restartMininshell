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
	free(tmp);
	close(file->fd);
}

void	init_heredoc(void)
{
	t_cmd	*cmd;
	t_file	*ptr;

	cmd = _shell()->head;
	while (cmd != NULL)
	{
		if (cmd->heredoc)
		{
			ptr = cmd->heredoc;
			while (ptr)
			{
				ask_for_input(ptr->filename, ptr);
				ptr = ptr->next;
			}
		}
		cmd = cmd->next;
	}
}
