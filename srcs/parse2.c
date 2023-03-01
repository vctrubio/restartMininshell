/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:20:02 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/27 15:55:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_do_quote(char **output, char c)
{
	char	*buff;
	char	*tmp;
	int		i;

	i = 1;
	buff = readline("dquote> ");
	add_history(buff);
	tmp = ft_strdup(buff);
	ft_stradd(&(*output), tmp);
	i += ft_strcount_char(tmp, c);
	free(buff);
	free(tmp);
	if (i % 2 != 0)
		ft_do_quote(output, c);
}

void	ft_do_pipe(char **output)
{
	char	*buff;
	char	*tmp;

	buff = readline("pipe> ");
	if (ft_strlen(buff) == 0)
		ft_do_pipe(output);
	else
	{
		add_history(buff);
		tmp = ft_strdup(buff);
		ft_stradd(&(*output), tmp);
		free(buff);
		free(tmp);
	}
}

int	vcheck(char *line)
{
	while (*line)
	{
		if (*line > 32 && *line < 127)
			return (0);
		line++;
	}
	return (1);
}
int	readline_check(char **p2line)
{
	char	*line;

	line = *p2line;
	if (vcheck(line))
	{
		free(*p2line);
		return (1);
	}
	if (ft_strexact("''", line) || ft_strexact("\"\"", line)
		|| ft_strexact("..", line) || ft_strexact(".", line))
	{
		if (ft_strexact(".", line))
		{
			printf("bash: .: filename argument required\n");
			printf("\t.: usage: . filename [arguments]\n");
		}
		else if (ft_strexact("..", line))
			printf("bash: ..: command not found\n");
		else
			printf("bash: : command not found\n");
		free(line);
		return (1);
	}
	if (!line || line[0] == '\0' || ft_strlen(line) == 0)
	{
		if (line[0] == '\0' || ft_strlen(line) == 0)
			free(line);
		return (1);
	}
	return (0);
}
