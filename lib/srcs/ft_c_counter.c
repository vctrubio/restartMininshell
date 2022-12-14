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
