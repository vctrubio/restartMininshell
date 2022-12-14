#include "../libft.h"

void	ft_strfree(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}
