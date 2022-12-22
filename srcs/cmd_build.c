#include "../include/minishell.h"

void	create_file(char *str, t_cmd *cmd)
{
	t_file	*file;
	t_file	*ptr;

	file = malloc(sizeof(t_file));
	file->filename = ft_strdup(str);
	file->type = cmd->type;
	file->next = NULL;
	if (cmd->file)
	{
		ptr = cmd->file;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = file;
	}
	else
		cmd->file = file;
}

void	create_infile(char *str, t_cmd *cmd)
{
	t_file	*file;
	t_file	*ptr;

	file = malloc(sizeof(t_file));
	file->filename = ft_strdup(str);
	file->type = R_IN;
	file->next = NULL;
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

int	is_new_redir(int c)
{
	return (c == '<' || c == '>');
}

t_cmd	*init_tcmd(char ***matrix)
{
	t_cmd	*cmd;
	int		i;

	cmd = ft_inicialize_cmd(*matrix);
	i = 0;
	while (**matrix != NULL)
	{
		if (!is_redir(***matrix))
		{
			if (ft_strexact("cat", **matrix))
				cmd->flag = 1;
			cmd->args[i++] = ft_strdup((**matrix));
		}
		else
		{
			set_redir(cmd, &matrix);
			if (**matrix && ft_strexact(**matrix, "|"))
				continue ;
			else
				break;
		}
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
	ptr = init_tcmd(&matrix);
	_shell()->head = ptr;
	while (*matrix != NULL)
	{
		ptr_next = init_tcmd(&matrix);
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
	print_tcmd(_shell()->head);
	init_heredoc();
	return (true);
}
