#include "../include/minishell.h"

void	do_child(t_cmd *cmd, char **path)
{
	*path = ft_get_exec_path(cmd->args);
	printf("path is %s,\n...\n", *path);
	execve(*path, cmd->args, _shell()->envp);
	printf("command not found....\n");
}

void	do_parent()
{
	printf("in the parent\n");
}

void	ft_loop(void)
{
	printf("running....\n");
	print_tcmd(_shell()->head);

	int fd[2];
	t_cmd	*cmd;
	char	*path;

	cmd = _shell()->head;
	if (!cmd)
		return ;
	while (cmd)
	{
		pipe(fd);
		if (fork() == 0)
			do_child(cmd, &path);
		else
		{
			do_parent();
			// if (path)
			// 	free(path);
		}
		cmd = cmd->next;
	}
}