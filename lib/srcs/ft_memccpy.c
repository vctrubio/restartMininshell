#include "../libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t l)
{
	size_t	i;
	char	*cdest;
	char	*csrc;

	i = 0;
	cdest = (char *)dest;
	csrc = (char *)src;
	while (i < l)
	{
		cdest[i] = csrc[i];
		if ((unsigned char)csrc[i] == (unsigned char)c)
			return ((char *)dest + i + 1);
		i++;
	}
	return (NULL);
}
