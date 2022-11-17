#include "../include/minishell.h"

void	open_pipe(int *fd, int i) //0 input, 1 output
{
	dup2(fd[i], i);
	close(fd[0]);
	close(fd[1]);
}

void	ft_exec(t_cmd *ptr)
{
	int		pid;
	char	*path;
	int		status;

	if (!ptr)
		return ;
	if (ptr->pipe)
	{
		pipe(ptr->pipe->fd);
		printf("we have created a pipe into %s t_cmd\n", ptr->args[0]);
	}
	pid = fork();
	if (pid == 0)
	{
		printf("in the CHILD of %s\n", ptr->args[0]);
		// if (ptr->pipe)
		// {
		// 	dup2(ptr->pipe->fd[1], 1);
		// 	close(ptr->pipe->fd[0]);
		// 	// close(ptr->pipe->fd[1]);
		// }
		if (ptr->prev)
		{
			// close(ptr->pipe->fd[1]);
		}
		path = ft_get_exec_path(ptr->args);
		printf("PATH EXEVE------%s (%s)-------\n\n", path, ptr->args[0]);
		execve(path, ptr->args, _shell()->envp);
		printf("child not execve- this is bad. -- parent still waiting for child to terminate\n");
		exit(1);
	}
	else
	{
		printf("\n--Before waitpid--In the Parent, waiting for the child of %s.\n", ptr->args[0]);
		waitpid(pid, &status, 0);
		printf("After waitpid\n");
		// if (ptr->pipe) 						  // if (ptr->pipe != NULL && ptr->next->next == NULL)
		// {
		// 	dup2(ptr->pipe->fd[0], 0);
		// 	close(ptr->pipe->fd[0]);
		// 	close(ptr->pipe->fd[1]);
		// 	// close(ptr->pipe->fd[0]);
		// 	printf("closing of pipe--\n");
		// }
		printf("Parent not execeve- this is good\n");
	}
	// 	free(path);  //NEED TO FREE
}

void	loop_execution(t_cmd *ptr)
{
	int	pid;
	int	status;

	if (ptr->pipe)
	{
		printf("sucess pipe 1\n");
		pipe(ptr->pipe->fd);
	}
	// if (ptr->prev && ptr->prev->pipe)
	// {
	// 	printf("sucess pipe 2\n");
	// 	pipe(ptr->pipe->fd);
	// }

	pid = fork();
	if (pid == 0)
	{
		printf("hello from child of %s\n", ptr->args[0]);
		if (ptr->pipe)
		{
			dup2(ptr->pipe->fd[1], 1);
			close(ptr->pipe->fd[0]);
		}
		// if (ptr->prev && ptr->prev->pipe)
		// {
		// 	printf("we have a pipe here!!!!!!!%s\n", ptr->prev->args[0]);
		// 	dup2(ptr->pipe->fd[1], ptr->prev->pipe->fd[1]);
		// 	// close(ptr->pipe->fd[1]);
		// }
		printf("doooooome\n");
		execve(ft_get_exec_path(ptr->args), ptr->args, _shell()->envp);
		printf("CHILD did NOT EXECVE\n");
		//have to signal kill
		exit(1);
	}
	else
	{
		wait(&status);
		// dup2(fd[1], 0);
		printf("hello from father\n");
		if (ptr->prev && ptr->prev->pipe)
		{
			printf("doit\n");
			execve(ft_get_exec_path(ptr->args), ptr->args, _shell()->envp);
		}
	}
}


void	do_execution(void)
{
	t_cmd	*ptr;

	ptr = _shell()->head;
	while (ptr)
	{
		printf("Make exec. %s\n", ptr->args[0]);
		loop_execution(ptr);
		// ft_exec(ptr);
		ptr = ptr->next;
	}
}

void	minishell(void)
{
	char	*line;

	while (43)
	{
		_shell()->valid_input = true;
		line = readline("---------> ");
		if (line == NULL)
		{
			printf("EXIT PROGRAM BUG\n");
			exit(0);
		}
		if (!line || line[0] == '\0')
			continue ;
		if (ft_strlen(line) == 0)
			continue ;
		if (ft_strexact(line, "exit"))
			break ;
		add_history(line);
		add_cmds(line_to_matrix(line));
		// print_tcmd(_shell()->head);
		do_execution();
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
}

int	main(int ac, char **av, char **ev)
{
	init_shell(ev);
	minishell();
	close_shell();
	return (1);
}


		// if (ptr->prev) //need to read from the pipe ptr->prev->pipe->fd[1] and dup into local ()
		// {
		// 	printf("WE HAVE PREV %s\n", ptr->prev->args[0]);
		// 	dup2(ptr->prev->pipe->fd[0], STDIN_FILENO);
		// 	// close(ptr->prev->pipe->fd[0]);
		// 	// close(ptr->prev->pipe->fd[1]);
		// }

		// if (ptr->pipe)
		// {
		// 	close(ptr->pipe->fd[1]); //output
		// 	// close(ptr->pipe->fd[0]); //input
		// }
		// if (ptr->prev && ptr->prev->pipe)
		// {
		// 	close(ptr->prev->pipe->fd[0]); //input
		// }