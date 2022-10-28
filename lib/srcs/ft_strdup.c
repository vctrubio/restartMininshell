#include "../libft.h"

char		*ft_strdup(char *str)
{
	char	*dest;
	int		i;

	dest = malloc(ft_strlen(str) * sizeof(char) + 1);
	if (dest == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
