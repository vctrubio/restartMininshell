#include "../include/minishell.h"

static void	child_proces(int *p, t_cmd *cmd)
{
	int		ret;
	t_file	*ptr;

	if (cmd->file)
	{
		printf("cmd: %s >< filename %s type %d\n", cmd->args[0], cmd->file->filename, cmd->type);
	}
	dup2(cmd->fd_in, 0);
	if (cmd->type == R_IN)
	{
		ptr = cmd->file;
		printf("REDIR IN %s\n", ptr->filename);
		ptr->fd = open(ptr->filename, O_RDONLY | 0777);
		printf("REDIR AFTER %d \n", ptr->fd);
		dup2(ptr->fd, 0);
	}

	if (cmd->type == R_OUT)
	{
		ptr = cmd->file;
		// printf("REDIR IN %s\n", ptr->filename);
		ptr->fd = open(ptr->filename,  O_WRONLY | O_CREAT | O_TRUNC , 0777);
		// printf("REDIR AFTER %d \n", ptr->fd);
		dup2(ptr->fd, 1);
	}
	else if (cmd->type == R_APP)
	{
		ptr = cmd->file;
		ptr->fd = open(ptr->filename,  O_WRONLY | O_CREAT | O_APPEND , 0777); // O_TRUNC IDK What that flag is tbh
		dup2(ptr->fd, 1);
	}
	else if (cmd->next) //&& there is no redir (onlly a pipe)
		dup2(p[1], 1);

	close(p[0]);
}

void	loop_execution(t_cmd *cmd)
{
	int		p[2];
	pid_t	pid;
	int		status;
	char	*path;
	int		ret;

	while (cmd)
	{
		pipe(p);
		path = ft_get_exec_path(cmd->args);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			child_proces(p, cmd);
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
			if (cmd->file)
				close(cmd->file->fd);
			cmd = cmd->next;
			if (cmd)
				cmd->fd_in = p[0];
			free(path);
		}
	}
	free_cmds(_shell()->head);
}
