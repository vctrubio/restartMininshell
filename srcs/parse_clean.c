#include "../include/minishell.h"
//Removing Quotes

char *parse_clean(char **p2str)
{
	char	*cpy;
	int		i;
	char	*str;

	str = *p2str;
	cpy = malloc(sizeof(char) * ft_strlen(str) + 1);
	i = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				cpy[i++] = *(str++);
		}
		else if (*str == '"')
		{
			str++;
			while (*str && *str != '"')
				cpy[i++] = *(str++);
		}
		else
			cpy[i++] = *str;
		str++;
	}
	cpy[i] = 0;
	free(*p2str);
	*p2str = cpy;
	printf("CPY %s-------------\n", cpy);
	return (cpy);
}
