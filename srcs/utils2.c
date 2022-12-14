#include "../include/minishell.h"

void	ft_swap2str(char **str1, char **str2)
{
	char	*tmp_str;

	tmp_str = ft_strdup(*str1);
	free(*str1);
	*str1 = ft_strdup(*str2);
	free(*str2);
	*str2 = ft_strdup(tmp_str);
	free(tmp_str);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
			&& c <= 'Z'))
		return (1);
	else
		return (0);
}
