#include "../libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dup;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	dup = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1 * sizeof(char));
	if (!dup)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		dup[i] = s2[j];
		j++;
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
