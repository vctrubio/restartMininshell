/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrubio < vrubio@student.42lisboa.com >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:26:24 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/22 11:26:25 by vrubio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_var_from_expansion(char *str, t_vars *vars)
{
	int	i;

	i = 0;
	ft_get_quotes_inner_outer(*(str + i), vars);
	if (((vars->outer_quote == 0 && vars->inner_quote == 0)
			|| (vars->inner_quote == 0 && vars->outer_quote == 2)
			|| (vars->outer_quote == 2 && vars->inner_quote == 1))
		&& (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i
				+ 1] == '?') && str[i + 1] != '\'' && str[i + 1] != '"'))
	{
		if (str && (str - 1) && (str - 2) && (*str - 2) == '$' && *(str
				- 1) == '?')
			return (0);
		else
			return (1);
	}
	return (0);
}

t_vars	ft_exp_helper(t_vars v, char *str)
{
	v.start = ++v.i;
	while (str[v.i] && (ft_isalnum(str[v.i]) || str[v.i] == '?'))
	{
		if (str[v.i] && (str[v.i] == '?'))
		{
			v.i++;
			break ;
		}
		ft_get_quotes_inner_outer(*(str + v.i), &v);
		v.i++;
		if (str[v.i] && (str[v.i] == '\'' || str[v.i] == '"'
				|| str[v.i] == '\''))
			break ;
	}
	v.tmp_str = ft_substr(str, v.start, v.i - v.start);
	v.tmp_str2 = ft_getenv(v.tmp_str, 0);
	if (v.tmp_str2)
		v.matrix[v.j++] = v.tmp_str2;
	free(v.tmp_str);
	return (v);
}

t_vars	ft_nexp_helper(t_vars v, char *str)
{
	v.start = v.i;
	v.i++;
	while (str[v.i] && !ft_is_var_from_expansion((str + v.i), &v))
		v.i++;
	v.tmp_str = ft_substr(str, v.start, v.i - v.start);
	v.matrix[v.j++] = ft_substr(str, v.start, v.i - v.start);
	free(v.tmp_str);
	return (v);
}

char	*ft_var_expansion(char *str)
{
	t_vars	v;

	ft_inicialize_vars(&v);
	v.j = 2;
	while (str[v.k])
	{
		if (str[v.k] == '\'' || str[v.k] == '"' || str[v.k] == '$')
			v.j++;
		v.k++;
	}
	v.matrix = ft_realloc(v.matrix, (v.j + 2) * sizeof(char *));
	v.j = 0;
	while (str[v.i])
	{
		v.start = v.i;
		if (ft_is_var_from_expansion((str + v.i), &v))
			v = ft_exp_helper(v, str);
		else
			v = ft_nexp_helper(v, str);
	}
	v.matrix[v.j] = NULL;
	v.tmp_str = ft_concat_multi(v.matrix, NULL);
	ft_matrix_free(v.matrix);
	free(str);
	return (v.tmp_str);
}

void	ft_get_quotes_inner_outer(char c, t_vars *vars)
{
	int	num;

	num = 0;
	if (c == '"')
		num = 2;
	else if (c == '\'')
		num = 1;
	if (num != 0)
	{
		if (vars->outer_quote == 0)
			vars->outer_quote = num;
		else if (vars->outer_quote == num)
			vars->outer_quote = 0;
		else
		{
			if (vars->inner_quote == 0)
				vars->inner_quote = num;
			else if (vars->inner_quote == num)
				vars->inner_quote = 0;
		}
	}
}
