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

//try with no i just pointer!
