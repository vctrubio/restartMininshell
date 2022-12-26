#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMANDS 10

typedef struct
{
	char	*command;
	char	*args[MAX_COMMANDS];
}			Command;

void	pipe_commands(Command *commands, int num_commands)
{
	int		i;
	int		pipes[2 * num_commands];
	int		j;
	pid_t	pid;
	Command	command;
	char	*command_str;
	int		arg_index;

	for (i = 0; i < num_commands; i++)
	{
		if (pipe(pipes + i * 2) < 0)
		{
			perror("pipe");
			exit(1);
		}
	}
	for (i = 0; i < num_commands; i++)
	{
		j = i * 2;
		pid = fork();
		if (pid == 0)
		{
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
			for (int k = 0; k < 2 * num_commands; k++)
			{
				close(pipes[k]);
			}
			command = commands[i];
			command_str = command.command;
			command.args[0] = strtok(command_str, " ");
			arg_index = 1;
			while ((command.args[arg_index] = strtok(NULL, " ")))
			{
				arg_index++;
			}
			command.args[arg_index] = NULL;
			execvp(command.args[0], command.args);
			perror("execvp");
			exit(1);
		}
		else if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
	}
	for (i = 0; i < 2 * num_commands; i++)
	{
		close(pipes[i]);
	}
	for (i = 0; i < num_commands; i++)
	{
		wait(NULL);
	}
}

// int	main(void)
// {
// 	int	num_commands;

// 	Command commands[MAX_COMMANDS] = {
// 		{"cat", {"", NULL}},
// 		{"cat", {"", NULL}},
// 		{"ls", {"", NULL}}};
// 	num_commands = 3;
// 	pipe_commands(commands, num_commands);
// 	return (0);
// }