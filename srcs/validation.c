/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:20:14 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/25 14:44:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_validate_pipe_matrix(char **line, int i, int j)
{
	if (i == 0 && j == 0)
		_shell()->valid_input = false;
	if (line[i + 1] && line[i + 1][0] == '|')
		_shell()->valid_input = false;
	if (line[i])
	{
		if (line[i][1])
		{
			if (line[i][1] == '|')
				_shell()->valid_input = false;
		}
	}
}

static void	ft_validate_redir_output_matrix(char **line, int i)
{
	if (line[i + 1])
	{
		if ((line[i + 1][0] == '>') || (line[i + 1][0] == '<'))
			_shell()->valid_input = false;
	}
	else
		_shell()->valid_input = false;
}

static void	ft_validate_redir_input_matrix(char **line, int i)
{
	if (line[i + 1])
	{
		if ((line[i + 1][0] == '>') || (line[i + 1][0] == '<'))
			_shell()->valid_input = false;
	}
	else
		_shell()->valid_input = false;
}

void	validate_rl(char **matrix)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (matrix[i])
	{
		j = -1;
		while (matrix[i][++j])
		{

			if (matrix[i][j] == '"' || matrix[i][j] == '\'')
			{
				c = matrix[i][j++];
				while (matrix[i][j] && matrix[i][j] != c)
					j++;
			}
			if (matrix[i][j] == '|')
				ft_validate_pipe_matrix(matrix, i, j);
			if (matrix[i][j] == '>')
				ft_validate_redir_output_matrix(matrix, i);
			if (matrix[i][j] == '<')
				ft_validate_redir_input_matrix(matrix, i);
		}
		i++;
	}
}
