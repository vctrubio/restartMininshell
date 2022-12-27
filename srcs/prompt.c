#include "../include/minishell.h"

char	*ft_prompt(void)
{
	char	*str;
	char	prompt[255];
	char	*tmp;

	str = getcwd(prompt, sizeof(prompt));
	while (*str)
		str++;
	while (*str != '/')
		str--;
	str++;
	if ( _shell()->exit_code == 0)
		tmp = ft_strdup("\033[0;32m");
	else if ( _shell()->exit_code == 127)
		tmp = ft_strdup("\033[0;31m");
	else
		return (ft_strjoin(str, "$> "));
	str = ft_strjoin(tmp, str);
	str = ft_strjoin(str, "$>\033[0m ");
	free(tmp);
	return (str);
}
