#include "../libft.h"

void	ft_strfree(char **str)
{
	int	i;
	
	i = 0;
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}