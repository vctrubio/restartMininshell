/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrubio < vrubio@student.42lisboa.com >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:56 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/22 15:19:57 by vrubio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_chk_n_exit_if_null_ppchar(char **matrix, char *error_str)
{
	if (matrix == NULL)
	{
		if (error_str == NULL)
			perror("Allocation ERROR");
		else
			perror(error_str);
		exit(EXIT_FAILURE);
	}
}

void	ft_chk_n_exit_if_null_pchar(char *str, char *error_str)
{
	if (str == NULL)
	{
		if (error_str == NULL)
			perror("Allocation ERROR");
		else
			perror(error_str);
		exit(EXIT_FAILURE);
	}
}

char	**ft_matrix_remove_col_by_index(char **matrix, int index)
{
	int		col_num;
	char	**list;
	int		i;
	int		j;

	list = NULL;
	col_num = ft_matrix_get_num_col(matrix);
	list = ft_realloc(list, (col_num) * sizeof(char *));
	ft_chk_n_exit_if_null_ppchar(list, NULL);
	i = 0;
	j = 0;
	while (i < col_num - 1)
	{
		if (i == index)
			i++;
		list[j] = ft_strdup(matrix[i]);
		ft_chk_n_exit_if_null_pchar(list[j], NULL);
		i++;
		j++;
	}
	list[j] = NULL;
	ft_matrix_free(matrix);
	return (list);
}

void	ft_print_matrix_add_str2line_start(char **matrix, char *str, char *glue)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		if (matrix[i][0] == '?' && matrix[i][1] == '=')
		{
			i++;
			continue ;
		}
		ft_putstr_fd(str, 1);
		if (glue != NULL)
			ft_putstr_fd(glue, 1);
		ft_putstr_fd(matrix[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return ;
}
