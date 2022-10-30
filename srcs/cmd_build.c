#include "../include/minishell.h"
//this is where it gets interesting

t_cmd	*init_tcmd(char **cmds)
{
	t_cmd	*cmd;

	print_arrays(cmds);
	cmd = malloc(sizeof(t_cmd));
	cmd->cmd = *cmds;
	while (*(++cmds) != NULL)
		printf("%s args... \n", *cmds);
	printf("cmd->cmd = %s\n", cmd->cmd);
	// (*cmds)++; // HELP i dont know
	// printf("%s args... \n", *cmds);
	cmd->type = NADA;
	return (cmd);
}

void	build_cmds(char **cmds)
{
	t_cmd	*ptr;

	printf("ft_build_cmds\n");
	//we return head
	ptr = init_tcmd(cmds);
	g_envp.head = ptr;
	//while we have cmds,
	//	ptr = to init_tcmd and we have to link it to our global head.
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