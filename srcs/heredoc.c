#include "../include/minishell.h"

static void	ask_for_input(char *word, t_file *file)
{
	char	*line;
	int		i;
	char	*tmp;

	i = 0;
	line = NULL;
	tmp = ft_strdup(".tmp.");
	file->heredoc = ft_strjoin(tmp, file->filename);
	file->fd = open(file->heredoc, O_RDWR | O_CREAT | O_TRUNC, 0777);
	while(1)
	{
		line = readline("heredoc>>");
		if (ft_strexact(line, word))
				break;
		write(file->fd, line, ft_strlen(line));
        write(file->fd, "\n", 1);
		free(line);
		line = NULL;
	}
	free(tmp);
	close(file->fd);
}

void	init_heredoc(void)
{
	t_cmd	*cmd;

	cmd = _shell()->head;
	while (cmd != NULL)
	{
		if (cmd->heredoc)
			ask_for_input(cmd->heredoc->filename, cmd->heredoc);
		cmd = cmd->next;
	}
}
