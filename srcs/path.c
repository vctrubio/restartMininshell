#include "../include/minishell.h"

int	ft_get_exec_path_chk_access(char *path, char **env_path, char ***matrix)
{
	if (access(path, F_OK) != -1)
	{
		free(*env_path);
		ft_matrix_free(*matrix);
		return (1);
	}
	return (0);
}

char	*ft_get_exec_path(char **argv)
{
	char	*env_path;
	char	*path;
	char	**matrix;
	char	*tmp_str;
	int		i;

	if (access(argv[0], F_OK) != -1)
		return (ft_strdup(argv[0]));
	tmp_str = ft_getenv("PATH", 1);
	if (!tmp_str)
		return (NULL);
	env_path = ft_strdup(tmp_str);
	free(tmp_str);
	matrix = ft_strsplit(env_path, ':');
	i = -1;
	while (matrix[++i] != NULL)
	{
		path = ft_concat3(matrix[i], "/", argv[0]);
		if (ft_get_exec_path_chk_access(path, &env_path, &(matrix)))
			return (path);
		free(path);
	}
	free(env_path);
	free_arrays(matrix);
	return (NULL);
}

char	*ft_getenv(char *name, int trimmed)
{
	int		i;
	char	**split;
	char	*ret;

	i = -1;
	if (ft_strexact(name, "?"))
		return (ft_itoa(_shell()->exit_code));
	while (_shell()->envp[++i] != NULL && name && ft_strncmp(_shell()->envp[i],
			name, ft_strlen(name)))
		;
	if (_shell()->envp[i][ft_strlen(name)] != '=')
		return (NULL);
	if (_shell()->envp[i] != NULL)
	{
		split = ft_strsplit(_shell()->envp[i], '=');
		if (split[1] == NULL)
			ret = NULL;
		else if (!trimmed)
			ret = ft_concat_string_between_chars(2, split[1], 2);
		else
			ret = ft_strdup(split[1]);
		ft_matrix_free(split);
		return (ret);
	}
	return (NULL);
}
