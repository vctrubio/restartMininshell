#include "../libft.h"

int	ft_atoi(const char *s)
{
	int	sign;
	int	n;
	int	valid;

	n = 0;
	sign = 1;
	valid = 0;
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		valid++;
		s++;
	}
	if (valid > 1)
		return (0);
	while (*s >= '0' && *s <= '9')
		n = n * 10 + *(s++) - '0';
	return (n * sign);
}
