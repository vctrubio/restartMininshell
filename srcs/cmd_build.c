#include "../include/minishell.h"
//this is where it gets interesting

static void	create_file(char *str, t_cmd *cmd)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	//TO WATCH OUT FOR cat >|ls
	file->filename = ft_strdup(str);
	file->type = cmd->type;
	file->next = NULL;
	if (cmd->file)
	{
		while (cmd->file->next)
			cmd->file = cmd->file->next;
		cmd->file->next = file;
	}
	else
		cmd->file = file;
}

void	set_redir(t_cmd *cmd, char ****str)
{
	if (ft_strexact(***str, "|"))
		;
	else if (ft_strexact(***str, ">"))
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
	else if (ft_strexact(***str, "<"))
	{
		cmd->type = R_IN;
		**(str) = **str + 1;
		create_file(***str, cmd);
	}
	else if (ft_strexact(***str, "<<"))
	{
		cmd->type = HEREDOC;
		**(str) = **str + 1;
		create_file(***str, cmd);
	}
	**(str) = **str + 1;
}

t_cmd	*init_tcmd(char ***matrix)
{
	t_cmd	*cmd;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	cmd->type = NADA;
	cmd->file = NULL;
	cmd->file = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->flag = 0;
	cmd->args = malloc((1 + ft_matrix_get_num_col(*matrix)) * sizeof(char **));
	i = 0;
	while (**matrix != NULL)
	{
		if (!is_redir(***matrix))
		{
			if (ft_strexact("cat", **matrix)) //or anything that reads from STDIN
			{
				cmd->flag = 1;
				//obviously this needs more validating
			}
			cmd->args[i++] = ft_strdup((**matrix));
		}
		else
		{
			set_redir(cmd, &matrix);
			break ;
		}
		*(matrix) = *matrix + 1;
	}
	cmd->args[i] = NULL;
	return (cmd);
}

void	build_cmds(char **matrix)
{
	t_cmd *ptr;
	t_cmd *ptr_next;
	char **ptr_to_free;

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

void	add_cmds(char **matrix)
{
	validate_rl(matrix);
	if (_shell()->valid_input == false)
		printf("INVALID USER INPUT... ERROR IN PARSING... TBD\n");
	build_cmds(matrix);
	// free_arrays(matrix);
}