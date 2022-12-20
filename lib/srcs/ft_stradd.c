#include "../libft.h"

void	ft_stradd(char **str, char *add)
{
	int	i;

	if (*str == NULL)
		return ;
	i = 0;
	while ((*str)[i])
		i++;
	(*str) = ft_realloc((*str), ft_strlen(*str) + ft_strlen(add) + 1);
	while (*add)
	{
		(*str)[i++] = *add;
		add++;
	}
	(*str)[i] = 0;
}
