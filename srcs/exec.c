#include "../include/minishell.h"

static void	child_proces(int *p, t_cmd *cmd)
{
	//int		ret;
	t_file	*ptr;
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
		ptr->fd = open(ptr->filename,  O_WRONLY | O_CREAT | O_TRUNC , 0777);
		dup2(ptr->fd, 1);
	}
	else if (cmd->type == R_APP)
	{
		ptr = cmd->file;
		ptr->fd = open(ptr->filename,  O_WRONLY | O_CREAT | O_APPEND , 0777);
		dup2(ptr->fd, 1);
	}
	else if (cmd->next)
		dup2(p[1], 1);
	close(cmd->fd_in);
	close(p[0]);
}

int	ft_setenv(char *name, char *value, int overwrite)
{
	int		i;
	char	*str;

	i = -1;
	if (value == NULL)
		str = ft_strjoin(name, "=");
	else
		str = ft_concat3(name, "=", value);
	if (str == NULL)
		return (0);
	while (_shell()->envp[++i] != NULL && name && ft_strncmp(_shell()->envp[i], name,
			ft_strlen(name)))
		;
	if (_shell()->envp[i] != NULL && overwrite == 1)
	{
		free(_shell()->envp[i]);
		_shell()->envp[i] = ft_strdup(str);
	}
	else if (_shell()->envp[i] == NULL)
		_shell()->envp = ft_matrix_push(_shell()->envp, str);
	free(str);
	return (1);
}

int	set_cd_folder_return_if_free_folder_or_not(char **argv,
												char **ptr2folder)
{
	char	*tmp_str;
	int		to_free;

	to_free = 1;
	if (argv[1] == NULL)
		*ptr2folder = ft_getenv("HOME", 1);
	else if (argv[1][0] == '-')
		*ptr2folder = ft_getenv("OLDPWD", 1);
	else if (argv[1][0] == '~')
	{
		tmp_str = ft_getenv("HOME", 1);
		*ptr2folder = ft_strjoin(tmp_str, argv[1] + 1);
		free(tmp_str);
	}
	else
	{
		*ptr2folder = argv[1];
		to_free = 0;
	}
	return (to_free);
}

int	ft_cd(char **argv)
{
	char	*folder;
	int		to_free;
	char	pwd[256];
	int		ret;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("getcwd() error");
	to_free = set_cd_folder_return_if_free_folder_or_not(argv, &folder);
	ret = chdir(folder);
	if (ret != 0)
		perror("minishell");
	ft_setenv("OLDPWD", pwd, 1);
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("getcwd() error");
	ft_setenv("PWD", pwd, 1);
	if (to_free)
		free(folder);
	return (ret * (-1));
}

int	ft_echo(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL && ft_strncmp(argv[i], "-n", 2) == 0)
		i++;
	while (argv[i] != NULL)
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (argv[1] == NULL || ft_strncmp(argv[1], "-n", 2) != 0
		|| (ft_strncmp(argv[1], "-n", 2) == 0 && argv[1][2]
			&& !isalpha(argv[1][2])))
		ft_putchar_fd('\n', 1);
	return (0);
}

int	ft_pwd(char **argv)
{
	char	cwd[256];

	(void)argv;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	else
		printf("%s\n", cwd);
	return (0);
}

void	ft_export_no_args(void)
{
	t_vars	vars;

	ft_inicialize_vars(&vars);
	vars.matrix = ft_matrix_dup(_shell()->envp, 0);
	while (vars.matrix[vars.l] != NULL)
	{
		while (vars.matrix[vars.k + 1] != NULL)
		{
			vars.i = ft_strlen(vars.matrix[vars.k]);
			vars.j = ft_strlen(vars.matrix[vars.k + 1]);
			if (vars.i > vars.j)
				vars.i = vars.j;
			if (ft_strncmp(vars.matrix[vars.k], vars.matrix[vars.k + 1],
					vars.i) > 0)
				ft_swap2str(&(vars.matrix[vars.k]), &(vars.matrix[vars.k + 1]));
			vars.k++;
		}
		vars.k = 0;
		vars.l++;
	}
	ft_print_matrix_add_str2line_start(vars.matrix, "declare -x", " ");
	ft_matrix_free(vars.matrix);
}

int	ft_export(char **argv)
{
	char	**name_value;
	t_vars	vars;

	ft_inicialize_vars(&vars);
	if (argv[1])
	{
		name_value = ft_strsplit(argv[1], '=');
		if (name_value[1])
			ft_setenv(name_value[0], name_value[1], 1);
		else
			ft_setenv(name_value[0], NULL, 1);
		ft_matrix_free(name_value);
		if (argv[2])
		{
			vars.i = 1;
			while (argv[++vars.i])
			{
				ft_putstr_fd("minishell: export \"", 2);
				ft_putstr_fd(argv[vars.i], 2);
				ft_putstr_fd("\": not an identifier\n", 2);
			}
			return (0);
		}
	}
	else
		ft_export_no_args();
	return (1);
}

int	ft_unset(char **argv)
{
	int	i;

	i = -1;
	while (_shell()->envp[++i] != NULL && ft_strncmp(_shell()->envp[i], argv[1],
			ft_strlen(argv[1])))
		;
	if (_shell()->envp[i] != NULL)
		_shell()->envp = ft_matrix_remove_col_by_index(_shell()->envp, i);
	return (0);
}

int	check_if_builtin(t_cmd *cmd)
{
	if (ft_strexact("pwd", cmd->args[0]))
		return (1);
	if (ft_strexact("echo", cmd->args[0]))
		return (1);
	if (ft_strexact("env", cmd->args[0]))
		return (1);
	if (ft_strexact("cd", cmd->args[0]))
		return (1);
	if (ft_strexact("export", cmd->args[0]))
		return (1);
	if (ft_strexact("unset", cmd->args[0]))
		return (1);
	return (0);
}

void	run_builtin(t_cmd *cmd)
{
	if (ft_strexact("pwd", cmd->args[0]))
		_shell()->exit_code = ft_pwd(cmd->args);
	if (ft_strexact("echo", cmd->args[0]))
		_shell()->exit_code = ft_echo(cmd->args);
	if (ft_strexact("env", cmd->args[0]))
		_shell()->exit_code = ft_env(cmd->args);
	if (ft_strexact("cd", cmd->args[0]))
		_shell()->exit_code = ft_cd(cmd->args);
	if (ft_strexact("export", cmd->args[0]))
		_shell()->exit_code = ft_export(cmd->args);
	if (ft_strexact("unset", cmd->args[0]))
		_shell()->exit_code = ft_unset(cmd->args);
}

// void clean_hidden_chars(char **p2str)
// {
// 	char	*cpy;
// 	int		i;
// 	char	*str;

// 	str = *p2str;
// 	cpy = malloc(sizeof(char) * ft_strlen(str) + 1);
// 	i = 0;

// 	while (*str)
// 	{
// 		if (*str == 2)
// 		{
// 			str++;
// 			while (*str && *str != 3)
// 				cpy[i++] = *(str++);
// 		}
// 		else
// 			cpy[i++] = *str;
// 		if(*str != '\0')
// 			str++;
// 	}
// 	cpy[i] = 0;
// 	free(*p2str);
// 	*p2str = cpy;
// }

void	loop_execution(t_cmd *cmd)
{
	int		p[2];
	pid_t	pid;
	int		status;
	char	*path;
	int		ret;

	while (cmd)
	{
		if (check_if_builtin(cmd))
		{
			run_builtin(cmd);
			cmd = cmd->next;
			continue;
		}
		if(*cmd->args==NULL)
		{
			cmd = cmd->next;
			continue;
		}
		path = ft_get_exec_path(cmd->args);
		if (!path)
		{
			
			print_arrays((cmd->args));
			printf("cmd->args %s-------------\n", *(cmd->args));
			printf("PATH %s-------------\n", path);
			printf("bash: la: command not found\n");
			_shell()->exit_code = 127;
			cmd = cmd->next;
			continue;
		}
		// printf("SHW E THE PATH\n");
		// printf("PATH %s-------------\n", path);
		pipe(p);
		pid = fork();
		if (pid == 0)
		{
			child_proces(p, cmd);
			ret = execve(path, cmd->args, _shell()->envp);
			// printf("bad execution %d\n", ret);
			exit(ret);
		}
		else
		{
			if (cmd->flag && cmd->next)
			{
				// printf("DO the magic code\n"); //execute the next cmd first....
				readline("r>");
				kill(pid, SIGKILL);
			}
			else
				waitpid(pid, &status, WUNTRACED);
			_shell()->exit_code = status/256;
			// printf("status CODE %d\n", _shell()->exit_code);
			close(p[1]);
			if (cmd->file)
			{
				while (cmd->file)
				{
					close(cmd->file->fd);
					cmd->file = cmd->file->next;
					if (cmd->file)
						loop_execution(cmd);
				}
			}
			cmd = cmd->next;
			if (cmd)
				cmd->fd_in = p[0];
			free(path);
		}
	}
}
