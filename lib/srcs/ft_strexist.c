#include "../libft.h"

int		ft_strexist(char *s, char c)
{
	while (c != *s)
	{
		if (*s == 0)
			return (0);
		s++;
	}
	return (1);
}