#include "../include/minishell.h"
//parsing of quotes

void	ft_do_quote(char **output, char c)
{
	char	*buff;
	char	*tmp;
	int		i;

	i = 1;
	buff = readline("dquote> ");
	add_history(buff);
	tmp = ft_strdup(buff);
	ft_stradd(&(*output), tmp);
	i += ft_strcount_char(tmp, c);
	free(buff);
	free(tmp);
	if (i % 2 != 0)
		ft_do_quote(output, c);
}
