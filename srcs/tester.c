#include "../include/minishell.h"

t_pipe	*init_tpipe(t_cmd *cmd)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	pipe->n_cmd = 0;
	pipe->i = 0;
	pipe->j = 0;
	pipe->path = NULL;
	while (cmd)
	{
			cmd = cmd->next;
			pipe->n_cmd++;
	}
	return (pipe);
}


void	setup_pipe(t_pipe *ptr)
{
	int	i;

	i = -1;
	ptr->pipes = malloc(sizeof(int) * 2 * ptr->n_cmd);
	while (++i < ptr->n_cmd)
	{
			if (pipe(ptr->pipes + i * 2) < 0)
			{
					perror("pipe");
					exit(1);
			}
	}
	printf("setup_pipe completed\n");
}

void	run_pipe(t_pipe *pipe, t_cmd *cmd)
{
	pid_t	pid;

	while (cmd)
	{
		pipe->j = pipe->i * 2;
		pipe->path = ft_get_exec_path(cmd->args);
				
		printf("-PATH-%s\n", pipe->path);
		pid = fork();
		if (pid == 0)
		{
			//redir_pipe(cmd 
		}
		else
		{

		}

		pipe->i++;
		cmd = cmd->next;
	}
}

void	close_pipe(t_pipe *pipe)
{
	int	i;
	int	wpid;
	int	status;

	i = 0;
	while (i < 2 * pipe->n_cmd)
			close(pipe->pipes[i++]);
	i = 0;
	while (i < pipe->n_cmd)
	{
			wpid = waitpid(-1, &status, 0);
			if (wpid < 0)
				perror("waitpid error\n");
			_shell()->exit_code = status / 256;
			i++;
	}
	if (pipe->path)
			free(pipe->path);
	free(pipe);
}

void	do_pipe(t_cmd *cmd)
{
	t_pipe	*pipe;

	pipe = init_tpipe(cmd);

	setup_pipe(pipe);
	
	run_pipe(pipe, cmd);

	printf("PIPE RAN %d\n", pipe->n_cmd);
	close_pipe(pipe);
}
