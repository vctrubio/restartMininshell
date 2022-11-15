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
	if (ptr->pipe != NULL)
	{
		pipe(ptr->pipe->fd);
		printf("we have a PIPELONA\n");
	}
	// printf("%s argsument\n", ptr->args[0]);
	pid = fork();
	if (pid == 0)
	{
		printf("we have a CHILD\n");
		if (ptr->pipe != NULL)
		{
			dup2(ptr->pipe->fd[1], 1);
			close(ptr->pipe->fd[1]);
			// close(ptr->pipe->fd[0]);
		}
		if (ptr->prev) //need to read from the pipe ptr->prev->pipe->fd[1] and dup into local ()
		{
			printf("WE HAVE PREV %s\n", ptr->prev->args[0]);
			dup2(ptr->prev->pipe->fd[0], STDIN_FILENO);
			close(ptr->prev->pipe->fd[0]);
			close(ptr->prev->pipe->fd[1]);
		}
		path = ft_get_exec_path(ptr->args);
		printf("WE HAVE PATH BEFORE EXEVE %s\n", path);
		execve(path, ptr->args, _shell()->envp);
	}
	else
	{
		printf("Before\n");
		waitpid(pid, &status, 0);
		printf("After\n");
		if (ptr->pipe != NULL) // if (ptr->pipe != NULL && ptr->next->next == NULL)
		{
			dup2(ptr->pipe->fd[0], 0);
			close(ptr->pipe->fd[0]);
		}
		printf("Parent not execeve\n");
	// if (path) //WHERE DO I FREE
	// 	free(path); 
	}
}

void	do_execution(void)
{
	t_cmd	*ptr;

	ptr = _shell()->head;
	while (ptr)
	{
		printf("Make exec. %s\n", ptr->args[0]);
		ft_exec(ptr);
		if (ptr->pipe)
			close(ptr->pipe->fd[1]); //It's necessary to close this so the STDOUT gets back to normal
		ptr = ptr->next;
	}
}

void	minishell(void)
{
	char	*line;

	while (43)
	{
		_shell()->valid_input = true;
		line = readline("> ");
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

void	init_shell(char **ev)
{
	t_envp	*shell;

	shell = _shell();
	shell->envp = ft_matrix_dup(ev, 0);
	shell->exit_code = 0;
}

void	close_shell(void)
{
	if (_shell()->head)
		free_cmds(_shell()->head);
	if (_shell()->envp)
		free_arrays(_shell()->envp);
}

int	main(int ac, char **av, char **ev)
{
	init_shell(ev);
	minishell();
	close_shell();
	return (1);
}
