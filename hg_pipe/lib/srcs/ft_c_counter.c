/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrubio < vrubio@student.42lisboa.com >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:00:45 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/22 11:00:46 by vrubio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	count_words(char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		while (*str == c && *str)
			str++;
		if (*str == 0)
			return (i);
		while (*str && *str != c)
			str++;
		if (*str == 0)
			return (i + 1);
		i++;
	}
	return (i);
}
