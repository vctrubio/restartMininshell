#include "../include/minishell.h"

static void	child_proces(int *p, t_cmd *cmd)
{
	t_file	*ptr;

	//int		ret;
	if (cmd->file_in)
	{
		ptr = cmd->file_in;
		ptr->fd = open(ptr->filename, O_RDONLY, 0777);
		if (ptr->fd < 0)
			perror("no such file or directory: !!!!!!!!!! DON't KNow how to handle error. TBD");
		cmd->fd_in = ptr->fd;
	}
	if (cmd->heredoc)
	{
		ptr = cmd->heredoc;
		ptr->fd = open(ptr->heredoc, O_RDONLY, 0777);
		if (ptr->fd < 0)
			perror("no such file or directory: !!!!!!!!!! DON't KNow how to handle error. TBD");
		cmd->fd_in = ptr->fd;
	}
	dup2(cmd->fd_in, 0);
	if (cmd->type == R_OUT)
	{
		ptr = cmd->file;
		ptr->fd = open(ptr->filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(ptr->fd, 1);
	}
	else if (cmd->type == R_APP)
	{
		ptr = cmd->file;
		ptr->fd = open(ptr->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
		dup2(ptr->fd, 1);
	}
	else if (cmd->next)
		dup2(p[1], 1);
	if (cmd->flag != 2)
		close(cmd->fd_in);
	close(p[0]);
}

void	loop_execution(t_cmd *cmd)
{
	int		p[2];
	pid_t	pid;
	int		status;
	char	*path;
	int		ret;
	t_file	*file;
	char	*tmpstr;
	int		bs_cat;

	bs_cat = 0;
	while (cmd)
	{
		if (*cmd->args == NULL)
		{
			cmd = cmd->next;
			continue ;
		}
		if (check_if_builtin_not_pipe(cmd))
		{
			_shell()->exit_code = run_builtin_not_piped(cmd);
			if (!cmd->next && !cmd->prev && ft_strexact("exit", cmd->args[0]))
				_shell()->exit = 1;
			cmd = cmd->next;
			continue ;
		}
		path = NULL;
		if (!check_if_builtin_2pipe(cmd))
			path = ft_get_exec_path(cmd->args);
		if (!check_if_builtin_2pipe(cmd) && !path)
		{
			printf("bash: %s: command not found\n", *(cmd->args));
			_shell()->exit_code = 127;
			cmd = cmd->next;
			continue ;
		}
		if (cmd)
			cmd->fd_in = p[0];
		if (cmd->flag && cmd->next && (ft_strexact("ls", (cmd->next)->args[0])
				|| ft_strexact("pwd", (cmd->next)->args[0])))
			cmd->flag = 2;
		pipe(p);
		pid = fork();
		if (pid == 0)
		{
			child_proces(p, cmd);
			if (check_if_builtin_2pipe(cmd))
				ret = run_builtin_2pipe(cmd);
			else
				ret = execve(path, cmd->args, _shell()->envp);
			exit(ret);
		}
		else
		{
			if (cmd->flag == 2)
			{
				bs_cat++;
				kill(pid, SIGKILL);
			}
			else
				waitpid(pid, &status, WUNTRACED);
			close(p[1]);
			if (cmd->file)
			{
				file = cmd->file;
				while (file)
				{
					close(file->fd);
					file = file->next;
					if (file)
						loop_execution(cmd);
				}
			}
			cmd = cmd->next;
			// if (cmd)
			// 	cmd->fd_in = p[0];
			if (path)
				free(path);
		}
	}
	_shell()->exit_code = status / 256;
	while (bs_cat--)
	{
		tmpstr = readline("");
		printf("\n");
		free(tmpstr);
	}
}
