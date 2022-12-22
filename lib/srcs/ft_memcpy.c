/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrubio < vrubio@student.42lisboa.com >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:00:23 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/22 11:00:24 by vrubio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	count;

	if (!dest && !src)
		return (0);
	count = 0;
	while (count < n)
	{
		((unsigned char *)dest)[count] = ((unsigned char *)src)[count];
		count++;
	}
	return (dest);
}
