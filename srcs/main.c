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
	// printf("we have a 2222\n");
	pid = fork();
	if (pid == 0)
	{
		printf("we have a CHILD\n");
		if (ptr->pipe != NULL)
			open_pipe(ptr->pipe->fd, 1);
		path = ft_get_exec_path(ptr->args);
		execve(path, ptr->args, _shell()->envp);
	}
	else
	{
		// printf("we have a PARENT\n");
		waitpid(pid, &status, WUNTRACED);
		if (ptr->pipe != NULL && ptr->next->next == NULL)
		{
			open_pipe(ptr->pipe->fd, 0);
			ptr = ptr->next;
			path = ft_get_exec_path(ptr->args);
			execve(path, ptr->args, _shell()->envp);
		}
		printf("Parent not execeve\n");
	// if (path) //WHERE DO I FREE
	// 	free(path); 
	}
}

void	do_execution(void)
{
	t_cmd	*ptr;
	char	*path;
	int		pid;
	int		status;
	int		saved_stdout;

	printf("Make exec.\n\n");
	ft_exec(_shell()->head);
	
	// if (path) //WHERE DO I FREE
	// 	free(path); 
}

void	minishell(void)
{
	char	*line;

	while (43)
	{
		_shell()->valid_input = true;
		line = readline("> ");
		if (ft_strlen(line) == 0)
			continue ;
		if (ft_strexact(line, "exit"))
			break ;
		add_history(line);
		add_cmds(line_to_matrix(line));
		print_tcmd(_shell()->head);
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
