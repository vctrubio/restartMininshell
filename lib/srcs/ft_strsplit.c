#include "../libft.h"

char		**ft_strsplit(char const *str, char c)
{
	char	**split;
	int		i;
	int		i2;
	int		cnt;

	i = 0;
	i2 = 0;
	cnt = 0;
	if (!(split = (char **)malloc(sizeof(char *) * (count_words((char *)str, c) +1))))
		return (0);
	while (cnt < count_words((char *)str, c) && count_words((char *)str, c) > 0)
	{
		while (str[i] == c && str[i])
			i++;
		i2 = i;
		while (str[i] != c && str[i])
			i++;
		split[cnt++] = ft_substr((char *)str, i2, i -i2);
	}
	split[cnt] = 0;
	return (split);
}