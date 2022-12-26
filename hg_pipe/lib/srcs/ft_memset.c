/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrubio < vrubio@student.42lisboa.com >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:00:08 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/22 11:00:14 by vrubio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *str, char c, size_t l)
{
	size_t	i;
	char	*s;

	s = (char *)str;
	i = 0;
	while (i < l)
		s[i++] = c;
	return (s);
}
