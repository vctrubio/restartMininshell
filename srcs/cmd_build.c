#include "../include/minishell.h"
//this is where it gets interesting

t_file	*create_file(char *str, t_type type)
{
	t_file *file;

	file = malloc(sizeof(t_file));
	file->filename = ft_strdup(str);
	file->type = type;
	//...
	return (file);
}

void	set_redir(t_cmd *cmd, char ****str)
{
	// if (ft_strexact(*str, ">") && *(str + 1) && ft_strexact(*(str + 1), "|")) //TO WATCH OUT FOR cat >|ls

	if (ft_strexact(***str, ">")) 
	{
		cmd->type = R_OUT;
		**(str) = **str + 1;
		cmd->file = create_file(***str, cmd->type);
	}
	else if (ft_strexact(***str, "|"))
	{
		cmd->type = PIPE;
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
	cmd->cmd = **matrix;
	printf("COPYING cmd->cmd = %s\n", cmd->cmd);
	i = 0;
	cmd->args = malloc((1+ft_matrix_get_num_col(*matrix))*sizeof(char**));
	*(matrix) = *matrix + 1;

	while (**matrix != NULL)
	{
		if (!is_redir(***matrix)) // | >> < << >
		{
			printf("%s args... \n", **matrix);
			cmd->args[i++] = ft_strdup((**matrix));
		}
		else
		{
			set_redir(cmd, &matrix); //*[ls][-la][>][file.txt]
			break;
		}
		*(matrix) = *matrix + 1;

	}
	cmd->args[i]=NULL;
	cmd->current_cmd_pos = **matrix;
	printf("POS = %s\n", **matrix);
	return (cmd);
}

void	build_cmds(char **matrix)
{
	t_cmd	*ptr;
	t_cmd	*ptr_next;
	
	printf("ft_build_cmd\n");
	ptr = init_tcmd(&matrix);
	g_envp.head = ptr;


	// *(matrix) = ptr->current_cmd_pos;
	while (*matrix != NULL)
	{
		// printf("in whileloop %s \n", *(matrix));
		ptr_next = init_tcmd(&matrix);
		ptr->next = ptr_next;
		ptr_next->prev = ptr;
		ptr = ptr->next;
	}
	print_tcmd(g_envp.head);
	//ls
	//1 cmd

	//ls > t.txt
	//1 cmd

	//ls | wc
	//2 cmd

}