#include "../include/minishell.h"

void	add_cmds(char **matrix)
{
	validate_rl(matrix);
	if (_shell()->valid_input == false)
		printf("INVALID USER INPUT... ERROR IN PARSING... TBD\n");
	build_cmds(matrix);
	// free_arrays(matrix);
}

void	do_execution(void)
{
	t_cmd	*ptr;
	char	*path;
	int		pid;
	int		status;
	int		saved_stdout;

	printf("Make exec.\n");
	ptr = _shell()->head;
	if (!ptr)
		return ;
	path = ft_get_exec_path(ptr->args);
	printf("pathi is %s\n", path);
	pid = fork();
	if (pid == 0)
	{
		if (ptr->pipe) //
		{
			printf("do_cmd_pipe\n");
			//READ N WRITE
			// ptr->pipe->pid = fork();
			// if (ptr->pipe->pid == 0)
			// 	printf("in the child\n");
			// else
			// 	printf("in the parent\n");

		}
		else if (ptr->file)
		{
			saved_stdout = dup(1);
			printf("WE found a file and need to dup[]\n");
			ptr->file->fd = open(ptr->file->filename,
									O_WRONLY | O_CREAT | O_APPEND,
									0777);
			dup2(ptr->file->fd, STDOUT_FILENO);
			close(ptr->file->fd);
		}
		execve(path, ptr->args, _shell()->envp);
		//dup2 to redirect STDIO back to standard saved saved_stdout
		printf("execve (SHOULD NOT SHOW) if execve is called succesfully\n");

	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
		free(path);
	}
}

void	minishell(void)
{
	char	*line;

	//ls -la > file.out
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
