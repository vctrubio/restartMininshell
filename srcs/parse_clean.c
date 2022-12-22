/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrubio < vrubio@student.42lisboa.com >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:57 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/22 15:19:58 by vrubio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*parse_clean(char **p2str)
{
	char	*cpy;
	int		i;
	char	*str;
	char	c;

	str = *p2str;
	cpy = malloc(sizeof(char) * ft_strlen(str) + 1);
	i = 0;
	while (*str)
	{
		if (*str == 2 || *str == '\'' || *str == '"')
		{
			c = *str++;
			while (*str && *str != c)
				cpy[i++] = *(str++);
		}
		else
			cpy[i++] = *str;
		if (*str)
			str++;
	}
	cpy[i] = 0;
	free(*p2str);
	*p2str = cpy;
	return (cpy);
}
