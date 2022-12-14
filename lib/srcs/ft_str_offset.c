#include "../libft.h"

char	*ft_str_offset(char *str, int i)
{
	char	*str2;
	int		i2;

	if (i >= ft_strlen(str))
		return (str);
	str2 = (char *)malloc(sizeof(char) * i + 1);
	i2 = 0;
	while (str[i] != 0)
	{
		str2[i2++] = str[i++];
	}
	str2[i2] = 0;
	ft_strfree(&str);
	return (str2);
}
