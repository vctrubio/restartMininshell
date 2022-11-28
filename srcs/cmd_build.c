#include "../include/minishell.h"

static void	create_file(char *str, t_cmd *cmd)
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

static void	create_infile(char *str, t_cmd *cmd)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	file->filename = ft_strdup(str);
	file->type = R_IN;
	file->next = NULL;
	if (cmd->file_in)
	{
		printf("ERROR READING FROM 2 FILES\n");  //TO BE HANDLED
	}
	else
		cmd->file_in = file;
}

static void	create_heredoc(char *str, t_cmd *cmd)
{
	t_file	*file;
	//t_file	*ptr;

	file = malloc(sizeof(t_file));
	file->filename = ft_strdup(str);
	file->type = HEREDOC;
	file->next = NULL;
	if (cmd->heredoc)
	{
		printf("ERROR READING FROM 2 FILES in HEREDOC\n");  //TO BE HANDLED
	}
	else
		cmd->heredoc = file;
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
		**(str) = **str + 1;
		create_infile(***str, cmd);
		**(str) = **str + 1;
		//IF 	if (***str == NULL) GONNA BREAK OUR CODE FOR NOW
		cmd->args[0] = ft_strdup((***str));
		cmd->args[1] = 0;
	}
	else if (ft_strexact(***str, "<<"))
	{
		cmd->type = HEREDOC;
		**(str) = **str + 1;
		create_heredoc(***str, cmd);
	}
	**(str) = **str + 1;
	if (***str && is_redir(****str)) //AND NOT HERE DOC
		set_redir(cmd, str);
}

t_cmd	*init_tcmd(char ***matrix)
{
	t_cmd	*cmd;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	cmd->type = NADA;
	cmd->file = NULL;
	cmd->file_in = NULL;
	cmd->heredoc = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->flag = 0;
	cmd->fd_in = 0;
	cmd->args = malloc((1 + ft_matrix_get_num_col(*matrix)) * sizeof(char **));
	i = 0;
	while (**matrix != NULL)
	{
		if (!is_redir(***matrix))
		{
			if (ft_strexact("cat", **matrix)) //or anything that reads from STDIN
				cmd->flag = 1;
			cmd->args[i++] = ft_strdup((**matrix));
		}
		else
		{
			set_redir(cmd, &matrix);
			break ;
		}
		*(matrix) = *matrix + 1;
	}
	if (!cmd->file_in)
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

void	ft_my_var_exansion(t_cmd *ptr)
{
	
	while (ptr!= NULL)
	{
		while(*(ptr->args))
		{
			printf("%s \n",*(ptr->args));
		}
	// 	if (needs_to_exanpd(str))
	// 		change_values(str);
		ptr=ptr->next;
	}
	//char	*cmd;
	//cmd = ft_var_expansion(*matrix)
}

bool	add_cmds(char **matrix)
{
	validate_rl(matrix);
	if (_shell()->valid_input == false)
	{
		printf("INVALID USER INPUT... ERROR IN PARSING... TBD\n");
		return (false);
	}
	else
		build_cmds(matrix);
	//HERE -> echo $PWD
	//-> echo /pwd/
	ft_my_var_exansion(_shell()->head);
	init_heredoc();
	return (true);	
}