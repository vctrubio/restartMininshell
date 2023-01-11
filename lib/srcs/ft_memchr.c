/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrubio < vrubio@student.42lisboa.com >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:00:25 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/22 11:00:26 by vrubio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t		i;
	char		find;
	const char	*rstr;

	find = (unsigned char)c;
	rstr = (const char *)str;
	i = 0;
	while (i < n)
	{
		if (rstr[i] == find)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
