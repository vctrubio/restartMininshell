/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:50 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/29 20:02:58 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_handler(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	if (signum == SIGINT)
	{
		if (pid == -1)
		{
			write(1, "\n", 1);
			// rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			write(1, "\n", 1);
	}
	if (signum == SIGQUIT)
		write(1, "\n", 1);
}

int	init_remove_qt(void)
{
	t_cmd	*ptr;
	int		i;

	ptr = _shell()->head;
	while (ptr)
	{
		i = 0;
		while (ptr->args[i])
		{
			parse_clean(&(ptr->args[i]));
			i++;
		}
		ptr = ptr->next;
	}
	return (1);
}

void	run_only_builtins(t_cmd *cmd)
{
	int	fd_output;
	int	original_stdout;

	fd_output = -42;
	original_stdout = dup(1);
	if (check_if_builtin(cmd))
	{
		redirect_input(cmd);
		fd_output = redirect_output(cmd);
		_shell()->exit_code = run_builtin(cmd);
		if (fd_output != -42)
		{
			dup2(original_stdout, 1);
			close(original_stdout);
			close(fd_output);
		}
		return ;
	}
}

void	minishell(void)
{
	char	*line;
	char	**matrix;

	while (!_shell()->exit)
	{
		_shell()->valid_input = true;
		line = readline("minishell$> ");
		if (line == NULL)
			exit(0);
		add_history(line);
		if (readline_check(&line))
			continue ;
		line = ft_var_expansion(line);
		matrix = line_to_matrix(line);
		if (add_cmds(matrix))
		{
			init_remove_qt();
			// print_tcmd(_shell()->head);
			pipe_commands(_shell()->head);
		}
		else
			free_arrays(matrix);
		minishell_clean(&line);
	}
	free(line);
}

int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	if (ac != 1)
		return (0);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	init_shell(ev);
	_shell()->exit_code = -42;
	minishell();
	close_shell();
	printf("exit\n");
	return (_shell()->exit_code);
}
