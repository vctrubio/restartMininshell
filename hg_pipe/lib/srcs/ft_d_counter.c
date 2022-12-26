/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrubio < vrubio@student.42lisboa.com >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:00:40 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/22 11:00:41 by vrubio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_d_counter(int n)
{
	size_t	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}
