#include "../include/minishell.h"

void	handle_files(t_cmd *cmd)
{
	t_file	*ptr;

	//check to see if file_in is already empty?
	if (cmd->file_in)
	{
		ptr = cmd->file_in;
		ptr->fd = open(ptr->filename, O_RDONLY, 0777);
		if (ptr->fd < 0)
			return ;
		cmd->fd_in = ptr->fd;
		printf("OK copied file_in work\n");
	}
	if (cmd->heredoc)
	{
		ptr = cmd->heredoc;
		ptr->fd = open(ptr->heredoc, O_RDONLY, 0777);
		if (ptr->fd < 0)
			return ;
		cmd->fd_in = ptr->fd;
	}

	if (cmd->file)
	{
		ptr = cmd->file; //maybe leak because same ptr used twice
		if (ptr->type == R_APP)
			ptr->fd = open(ptr->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (ptr->type == R_OUT)
			ptr->fd = open(ptr->filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
}

void	handle_pipe(t_cmd *cmd, int *fd)
{
	if (cmd->fd_in)
	{
		printf("reading/has a file_in\n");
		dup2(cmd->fd_in, 0);
	}
	if (cmd->file)
	{
		printf("reading/has a file_out\n");
		dup2(cmd->file->fd, 1);
	}
	else if (cmd->next)
	{
		printf("writting to next cmd\n");
		dup2(cmd->next->fd_in, 1);
		close(fd[1]);
	}
}


void	do_child(t_cmd *cmd, int *fd, char **path)
{
	int		ptr_out;
	
	*path = ft_get_exec_path(cmd->args);
	printf("path is %s,\n...\n", *path);

	handle_files(cmd);
	handle_pipe(cmd, fd);
	execve(*path, cmd->args, _shell()->envp);
	printf("command not found....\n");

}

void	do_parent()
{
	int status;

	waitpid(0, &status, 0);
	printf("\n--------in the parent\n");
	//set return code

}

void	ft_loop(void)
{
	printf("running....\n");
	print_tcmd(_shell()->head);

	int 	fd[2];
	t_cmd	*cmd;
	char	*path;
	
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
		if (fork() == 0)
		{
			do_child(cmd, fd, &path);
		}
		else
		{
			do_parent();
			// if (path)
			// 	free(path); idk why but doesnt want to 
		}
		printf(",\n");
		cmd = cmd->next;
	}
}