#include "../include/minishell.h"

void	print_error(char *error_str1, char *error_str2)
{
	char	*tmpstr;
	char	*tmpstr2;

	tmpstr = ft_concat3("bash: ", error_str1, ": ");
	tmpstr2 = ft_strjoin(tmpstr, error_str2);
	printf("%s\n", tmpstr2);
	free(tmpstr);
	free(tmpstr2);
}

void	print_perror(char *error_str1)
{
	char	*tmpstr;

	tmpstr = ft_strjoin("bash: ", error_str1);
	perror(tmpstr);
	free(tmpstr);
}
