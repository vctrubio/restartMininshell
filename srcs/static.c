#include "../include/minishell.h"
//static calls

// t_cmd	*ptr_to_cmd(void) 
// {
// 	static t_cmd	cmd_lucas;

// 	return (&cmd_lucas); //HERE
// }

// int		main()
// {
// 	t_cmd	*mycmd;

// 	mycmd = ptr_to_cmd(); //get
// 	mycmd->cmd = "HI"; //set (updating cmd_lucas)
// }



// typedef struct s_envp
// {
// 	char		**envp;
// 	t_cmd		*head;
// 	char		*path;
// 	int			exit_code;
// 	bool		valid_input;
// }				t_envp;