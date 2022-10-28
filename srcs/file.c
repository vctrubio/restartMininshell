
#include "../include/minishell.h"

void _file_close(int fd[2])
{
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

int _file_create(int fd[2], char *path, int mode)
{
	fd[0] = open(path, O_CREAT | O_WRONLY | mode, 0644);
	if (fd[0] > 0)
	{
		fd[1] = dup(1);
		dup2(fd[0], 1);
	}
	else
		printf("Minishell: %s: Permission denied\n", path);
	return (!(fd[0] > 2));
}
