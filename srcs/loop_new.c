#include "../include/minishell.h"

void	do_child(t_cmd *cmd, int *fd, char **path)
{
	*path = ft_get_exec_path(cmd->args);
	printf("path is %s,\n...\n", *path);
	if (cmd->file)
		fd[1] = STDOUT_FILENO;
	
	t_file *ptr;
	
	if (cmd->file_in)
	{
		ptr = cmd->file_in;
		ptr->fd = open(ptr->filename, O_RDONLY, 0777);
		if (ptr->fd < 0)
			return ;
		cmd->fd_in = ptr->fd;
		printf("OK should work\n");
	} //else if heredoc

	if (cmd->file)
	{
		
	}
	else if (cmd->next)
	{

	}

	dup2(cmd->fd_in, 0);
	close(fd[0]);
	execve(*path, cmd->args, _shell()->envp);
	printf("command not found....\n");


}

void	do_parent()
{
	printf("in the parent\n");
	//set return code

}

void	ft_loop(void)
{
	printf("running....\n");
	print_tcmd(_shell()->head);

	int 	fd[2];
	t_cmd	*cmd;
	char	*path;
	pid_t	pid;
	int		status;

	cmd = _shell()->head;
	if (!cmd)
		return ;
	if (ft_strexact(cmd->args[0], "exit"))
	{
		printf("do exit....\n");
		exit(1);
	}
	while (cmd)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{

			do_child(cmd, fd, &path);
		}
		else
		{
			waitpid(0, &status, 0);
			close(fd[1]);
			do_parent();
			// if (path)
			// 	free(path); idk why but doesnt want to 
		}
		printf(",\n");
		cmd = cmd->next;
	}
}