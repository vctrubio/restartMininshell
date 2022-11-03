#include "../include/minishell.h"
//this is where it gets interesting

t_file	*create_file(char *str, t_type type)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	file->filename = ft_strdup(str);
	file->type = type;
	//...
	return (file);
}

void	set_redir(t_cmd *cmd, char ****str)
{
	// if (ft_strexact(*str, ">") && *(str + 1) && ft_strexact(*(str + 1), "|"))
	//TO WATCH OUT FOR cat >|ls
	if (ft_strexact(***str, "|"))
		cmd->type = PIPE;
	else if (ft_strexact(***str, ">"))
	{
		cmd->type = R_OUT;
		**(str) = **str + 1;
		cmd->file = create_file(***str, cmd->type);
	}
	else if (ft_strexact(***str, ">>"))
	{
		cmd->type = R_APP;
		**(str) = **str + 1;
		cmd->file = create_file(***str, cmd->type);
	}
	else if (ft_strexact(***str, "<"))
	{
		cmd->type = R_IN;
		**(str) = **str + 1;
		cmd->file = create_file(***str, cmd->type);
	}
	else if (ft_strexact(***str, "<<"))
	{
		cmd->type = HEREDOC;
		**(str) = **str + 1;
		cmd->file = create_file(***str, cmd->type);
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
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->fd = -1;
	cmd->args = malloc((1 + ft_matrix_get_num_col(*matrix)) * sizeof(char **));
	i = 0;
	while (**matrix != NULL)
	{
		if (!is_redir(***matrix))
			cmd->args[i++] = ft_strdup((**matrix));
		else
		{
			set_redir(cmd, &matrix); //*[ls][-la][>][file.txt]
			//while !is_redir(***matrix) (check for > file1 > file2 >> file3)
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