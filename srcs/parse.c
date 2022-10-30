#include "../include/minishell.h"
//parsing of quotes

static void	ft_do_quote(char **output, char c)
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

static char	*buffer_quotes(char **buff, char c, char *str, int i)
{
	str[(i)++] = *(*buff)++;
	while (**buff && **buff != c)
		str[(i)++] = *(*buff)++;
	if (**buff == c)
		str[(i)++] = *(*buff)++;
	return (str);
}

static char	*buffer_scan_for_quotes(char *str)
{
	int		i;
	int		f;
	char	c;
	char	k;

	f = 0;
	k = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (f++ == 0)
				c = str[i];
		}
		if (str[i] == c)
			k++;
	}
	if (k % 2 != 0)
		ft_do_quote(&str, c);
	return (str);
}

static char	*buffer_to_string(char **buff)
{
	char	*str;
	int		i;

	str = calloc(sizeof(char), (ft_strlen(*buff) + 1));
	i = 0;
	while (**buff)
	{
		i = ft_strlen(str);
		if (ft_isspace(**buff))
			break ;
		if (is_redir(**buff))
		{
			if (i != 0)
				return (str);
			str[i++] = *(*buff)++;
			if (**buff == str[i - 1])
				str[i++] = *(*buff)++;
			return (str);
		}
		if ((**buff == '\'' || **buff == '"') && *(*buff + 1) == **buff)
		{
			(*buff)++;
			(*buff)++;
		}
		if ((**buff == '\'' || **buff == '"') && (**buff + 1 != **buff))
			str = buffer_quotes(&(*buff), **buff, str, i);
		else if (**buff)
			str[i++] = *(*buff)++;
	}
	return (buffer_scan_for_quotes(str));
}

char	**line_to_matrix(char *line)
{
	char	**matrix;
	int		i;

	matrix = malloc(sizeof(char *) * (r_size(line) + 1));
	i = 0;
	while (*line)
	{
		while (ft_isspace(*line))
			line++;
		if (!line || ft_strlen(line) == 0)
			break ;
		matrix[i++] = buffer_to_string(&line);
	}
	matrix[i] = 0;
	return (matrix);
}
