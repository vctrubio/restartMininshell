/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hg_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:17:04 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/12/27 16:00:28 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_cmds(t_cmd *cmd)
{
	int		i;
	t_cmd	*curr;

	i = 0;
	curr = cmd;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

int	run_if_first_level_builtins_set_path(t_cmd **curr, char **path,
		int *num_commands, int *i)
{
	i[3] = 0;
	if (*path)
		free(*path);
	*path = ft_get_exec_path((*curr)->args);
	if (*path && access(*path, X_OK) != 0)
	{
		printf("bash: %s: Permission denied\n", ((*curr)->args)[0]);
		_shell()->exit_code = 126;
		i[3] = 1;
	}
	if (!check_if_builtin((*curr)) && !*path)
	{
		printf("bash: %s: command not found\n", ((*curr)->args)[0]);
		_shell()->exit_code = 127;
		i[3] = 1;
	}
	if (i[3] == 1)
	{
		*curr = (*curr)->next;
		*i = *i + 1;
		*num_commands = *num_commands - 1;
		i[3] = 0;
		return (1);
	}
	return (0);
}

void	pipe_commands_child_n_error(pid_t pid, t_cmd *curr, int *pipes,
		char *path, int *i)
{
	if (pid == 0)
	{
		pipe_commands_dup_n_close_pipes(curr, pipes, i[2], i[0], i[1]);
		if (check_if_builtin(curr))
			exit(run_builtin(curr));
		else
			exit(execve(path, curr->args, _shell()->envp));
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
}

// i[0] = i
// i[1] = j
// i[2] = num_commands
// i[3] = just free index
void	pipe_commands(t_cmd *cmd)
{
	int		i[4];
	int		*pipes;
	pid_t	pid;
	t_cmd	*curr;
	char	*path;

	if (cmd->args[0] == NULL)
		return ;
	path = NULL;
	i[2] = count_cmds(cmd);
	pipes = malloc(sizeof(int) * 2 * i[2]);
	pipe_commands_build_pipes(pipes, i[2]);
	curr = cmd;
	i[0] = 0;
	if (check_if_builtin_not_pipe(curr))
		_shell()->exit_code = run_builtin((curr));
	else
	{
		while (curr)
		{
			i[1] = i[0] * 2;
			if (run_if_first_level_builtins_set_path(&curr, &path, &i[2], &i[0]))
				continue ;
			pid = fork();
			pipe_commands_child_n_error(pid, curr, pipes, path, i);
			i[0]++;
			curr = curr->next;
		}
	}
	pipe_commands_cleanup(i[2], pipes, path);
}
