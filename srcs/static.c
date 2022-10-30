#include "../include/minishell.h"
//static calls

t_envp	*_shell(void)
{
	static t_envp enviroment;

	// printf("%p addres of enviroment\n", &enviroment);
	return (&enviroment);
}