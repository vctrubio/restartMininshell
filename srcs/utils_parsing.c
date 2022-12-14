#include "../include/minishell.h"

int	ft_strcount_char(char *str, char l)
{
	int	i;

	i = 0;
	if (!str || !l)
		return (0);
	while (*str)
	{
		if (*str == l)
			i++;
		str++;
	}
	return (i);
}

int	is_redir(int c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	r_size(char *s)
{
	int	is_special;
	int	size;

	size = 0;
	is_special = -1;
	while (s && *s)
	{
		if (ft_isspace(*s))
		{
			if (is_special != 0)
				is_special = 0;
		}
		else if (is_redir(*s))
		{
			is_special = 1;
			size++;
		}
		else
		{
			if (is_special != 2)
			{
				is_special = 2;
				size++;
			}
		}
		s++;
	}
	return (size);
}
