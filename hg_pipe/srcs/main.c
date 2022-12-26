/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:50 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/26 12:18:45 by codespace        ###   ########.fr       */
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
			rl_replace_line("", 0);
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
	if (ft_strexact("exit", cmd->args[0]))
	{
		_shell()->exit = 1;
		return ;
	}
	else if (check_if_builtin(cmd))
	{
		redirect_input(cmd);
		printf("\nINSIDE  CHECK BUILTINs\n");
		redirect_output(cmd);
		_shell()->exit_code = run_builtin(cmd);
		//ERROR STDOUT is not returning to default (no problem inside pipes but outside is not good)
		//dup2(STDOUT_FILENO, STDOUT_FILENO);
		return ;
	}
}

void	minishell(void)
{
	char	*line;
	t_cmd	original_cmd;
	char	**matrix;

	while (!_shell()->exit)
	{
		_shell()->valid_input = true;
		line = readline("minishell.42> ");
		if (line == NULL)
			exit(0);
		if (readline_check(&line))
			continue ;
		add_history(line);
		line = ft_var_expansion(line);
		matrix = line_to_matrix(line);
		if (add_cmds(matrix) && init_remove_qt())
		{
			original_cmd = *(_shell()->head);
			print_tcmd(_shell()->head);
			if (!((_shell()->head)->next) && check_if_builtin(_shell()->head))
				run_only_builtins(_shell()->head);
			else
				pipe_commands(_shell()->head);
		}
		else
			free_arrays(matrix);
		minishell_clean(&line, original_cmd);
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
	minishell();
	close_shell();
	printf("exit\n");
	return (_shell()->exit_code);
}
