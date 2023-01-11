/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrubio < vrubio@student.42lisboa.com >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:00:18 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/22 11:00:19 by vrubio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*str1;
	unsigned const char	*str2;
	size_t				i;

	str1 = (unsigned char *)dest;
	str2 = (unsigned const char *)src;
	i = 0;
	if (str1 == NULL && str2 == NULL)
		return (NULL);
	if (str2 < str1)
	{
		while (n-- > 0)
			str1[n] = str2[n];
	}
	else
	{
		while (i < n)
		{
			str1[i] = str2[i];
			i++;
		}
	}
	return (dest);
}
