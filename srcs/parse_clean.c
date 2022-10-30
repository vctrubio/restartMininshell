#include "../include/minishell.h"
//Removing Quotes

static void ft_squote(char **cpy, char **str)
{
	int i;

	i = ft_strlen(*cpy);
	(*str)++;
	while (**str != '\'' && **str)
		(*cpy)[i++] = *(*str)++;
}

static void ft_db_quote(char **cpy, char **str)
{
	int i;

	i = 0;
	(*str)++;
	while (**str != '"' && **str)
	{
		i = ft_strlen(*cpy);
		if (**str == '$' && (**str + 1 != '\'' || **str + 1 != '"' || **str + 1 !='$'))
			dollar_for_money(cpy, str);
		else
			(*cpy)[i] = *(*str)++;
	}
}

void	dollar_for_money(char **outup, char **input) //TO-DO, rtn $PWD as pwd...
{

}

char *parse_clean(char *str)
{
	int i;
	char *cpy;

	// printf("intro to parse_clean of (%s)\n", str);
	i = 0;
	cpy = calloc(100, 1); // because if we have $PWD, we dont know how long the actual path is.... //CALLOC can we use?
	while (*str)
	{
		i = ft_strlen(cpy);
		if (*str == '\'')
			ft_squote(&cpy, &str);
		else if (*str == '"')
			ft_db_quote(&cpy, &str);
		else if (*str == '$')
			dollar_for_money(&cpy, &str);
		else
			cpy[i] = *(str++);
	}
	cpy[ft_strlen(cpy) + 1] = 0;
	// printf("returning cpy: %s: \n", cpy);
	//need to free the str also
	return (cpy);
}
