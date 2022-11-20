#include "../include/minishell.h"

static void	child_proces(int fd_in, int *p, t_cmd *cmd)
{
	int		ret;
	
	//if redir-
	if (cmd->file)
	{
		printf("cmd: %s >< filename %s \n", cmd->args[0], cmd->file->filename);

	}
	dup2(fd_in, 0);
	if (cmd->next)
		dup2(p[1], 1);
	close(p[0]);
}

void	loop_execution(t_cmd *cmd)
{
	int		p[2];
	pid_t	pid;
	int		fd_in;
	int		status;
	char	*path;
	int		ret;

	fd_in = 0;
	while (cmd)
	{
		pipe(p);
		path = ft_get_exec_path(cmd->args);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			child_proces(fd_in, p, cmd);
			ret = execve(path, cmd->args, _shell()->envp);
			printf("bad execution\n");
			exit(ret);
		}
		else
		{
			if (cmd->flag && cmd->next) //Fixing
			{
				// printf("DO the magic code\n"); //execute the next cmd first....
				readline("r>");
				kill(pid, SIGKILL);
			}
			else
				waitpid(pid, &status, WUNTRACED);
			close(p[1]);
			fd_in = p[0];
			cmd = cmd->next;
			free(path);
		}
	}
	free_cmds(_shell()->head);
}
