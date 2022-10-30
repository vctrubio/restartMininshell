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

void	set_redir(t_cmd *cmd, char ***str)
{
	// if (ft_strexact(*str, ">") && *(str + 1) && ft_strexact(*(str + 1), "|")) //TO WATCH OUT FOR cat >|ls

	if (ft_strexact(**str, ">")) 
	{
		cmd->type = R_OUT;
		*(str) = *str + 1;
		cmd->file = create_file(**str, cmd->type);
	}
	else if (ft_strexact(**str, "|"))
	{
		cmd->type = PIPE;
	}
	*(str) = *str + 1;
}

t_cmd	*init_tcmd(char **matrix)
{
	t_cmd	*cmd;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	cmd->type = NADA;
	cmd->file = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->fd = -1;
	cmd->cmd = *matrix;
	printf("COPYING cmd->cmd = %s\n", cmd->cmd);
	i = 0;
	cmd->args = malloc((1+ft_matrix_get_num_col(matrix))*sizeof(char**));
	while (*(++matrix) != NULL)
	{
		// printf("%s args... \n", *matrix);
		if (!is_redir(**matrix)) // | >> < << >
			cmd->args[i++] = ft_strdup(*(matrix));
		else
		{
			set_redir(cmd, &matrix); //*[ls][-la][>][file.txt]
			break;
		}
	}
	cmd->args[i]=NULL;
	cmd->current_cmd_pos = *matrix;
	printf("POS = %s\n", *matrix);
	return (cmd);
}

void	build_cmds(char **matrix)
{
	t_cmd	*ptr;
	t_cmd	*ptr_next;
	
	printf("ft_build_cmd\n");
	ptr = init_tcmd(matrix);
	// print_tcmd(ptr);
	g_envp.head = ptr;
	*(matrix) = ptr->current_cmd_pos;
	while (*(matrix) != NULL)
	{
		
		// printf("in whileloop %s \n", *(matrix));
		ptr_next = init_tcmd(matrix);
		ptr->next = ptr_next;
		ptr_next->prev = ptr;
		ptr = ptr->next;
		if (ptr_next->current_cmd_pos == NULL)
			break;
		else
			*(matrix) = ptr->current_cmd_pos;
	}
	print_tcmd(g_envp.head);
	//we return head
	//ls
	//1 cmd

	//ls > t.txt
	//1 cmd

	//ls | wc
	//2 cmd

}

/* EXAMPLE 1: ls -la > text.txt
t_cmd	*cmd(malloc)

cmd->cmd = ls
cmd->args = -la
cmd->type = R_OUT
cmd->next = NULL

t_file	*file(malloc)
cmd->next = cmd2;


// EXAMPLE 2: pwd|ls
t_cmd	*t(malloc)
t->cmd	=pwd
t->args =NULL;
t->type = PIPE
t->next = t2

t_cmd	*t2(malloc)
t->cmd	=ls

*/