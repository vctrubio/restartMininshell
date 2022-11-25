#include "../include/minishell.h"

static void	ask_for_input(t_cmd *cmd)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while(1)
	{
		line = readline(">>");
		if (line == cmd->args[0])
				break;
		cmd->args[i++] = ft_strdup(line);
		free(line);
		line = NULL;
	}
}

void	create_heredoc(t_cmd *cmd)
{
	char	*word;
	char	*itr;
	t_file	*file;
	int		i;

	word = cmd->args[i++];
	printf("%s HERE AT HEREDOC:\n", word);
	if (!(cmd->args[i]))
			ask_for_input(cmd);

}
