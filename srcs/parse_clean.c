#include "../include/minishell.h"
//Removing Quotes

char *parse_clean(char *str)
{
	char	*cpy;
	int		i;

	// printf("intro to parse_clean of (%s)\n", str);
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
	free(str);
	return (cpy);
}
