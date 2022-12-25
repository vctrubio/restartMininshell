#include "../include/minishell.h"

int get_no_pipe(t_cmd *cmd)
{
	int i;

	i = 1;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}


// void loop_execution(t_cmd *cmd)
// {
// 	int **p[2];
// 	pid_t pid;
// 	char *path;
// 	int size;
// 	int i;
// 	int	j;

// 	size = get_no_pipe(cmd);
// 	printf("printing loop...\n");
// 	print_tcmd(_shell()->head);
// 	i = 0;
// 	while (i < size)
// 	{
// 		if (pipe(p + i * 2) < 0)
// 		{
// 			perror("pipe");
// 			exit(1);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < size && cmd)
// 	{
// 		j = i * 2;
// 		// if (loop_part1(&cmd, &path))
// 		// 	continue ;
// 		// if (cmd && cmd->prev == NULL)
// 		// 	cmd->fd_in = p[0];
// 		// pipe(p);
// 		// pid = fork();
// 		// if (pid == 0)
// 		// 	loop_child(cmd, p, path);
// 		// else
// 		// {
// 		// 	loop_parent(&cmd, &pid, p);
// 		// 	if (path)
// 		// 		free(path);
// 		// }
// 		i++;
// 	}
// 	i = 0;

// 	while (i < size)
// 	{
// 		wait(NULL);
// 		i++;
// 	}
// }
