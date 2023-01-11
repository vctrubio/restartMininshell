#include "../include/minishell.h"

void	pipe_commands_cleanup(int num_commands, int *pipes, char *path)
{
	int	i;
	int	status;
	int	wpid;

	i = 0;
	while (i < 2 * num_commands)
	{
		close(pipes[i]);
		i++;
	}
	i = 0;
	while (i < num_commands)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid < 0)
		{
			// perror("waitpid");
			// exit(1);
		}
		_shell()->exit_code = status / 256;
		i++;
	}
	if (path)
		free(path);
	free(pipes);
}

void	pipe_commands_build_pipes(int *pipes, int num_commands)
{
	int	i;

	if (pipes == NULL)
	{
		perror("malloc");
		exit(1);
	}
	i = 0;
	while (i < num_commands)
	{
		if (pipe(pipes + i * 2) < 0)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
}

void	pipe_commands_dup_n_close_pipes(t_cmd *curr, int *pipes,
		int num_commands, int i, int j)
{
	redirect_input(curr);
	if (i > 0)
	{
		if (dup2(pipes[j - 2], STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
	}
	if (i < num_commands - 1)
	{
		if (dup2(pipes[j + 1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
	}
	i = 0;
	while (i < 2 * num_commands)
	{
		close(pipes[i]);
		i++;
	}
	redirect_output(curr);
}