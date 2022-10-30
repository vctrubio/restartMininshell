#include "../include/minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = malloc(size);
	if (new_ptr == NULL)
	{
		perror("malloc failed!");
		exit(EXIT_FAILURE);
	}
	ft_memset(new_ptr, 0, size);
	ft_memcpy(new_ptr, ptr, size); // void	*ft_memcpy(void *dest, const void *src, size_t n)
	free(ptr);
	return (new_ptr);
}

void	ft_chk_n_exit_if_null_ppchar(char **matrix, char *error_str)
{
	if (matrix == NULL)
	{
		if (error_str == NULL)
			perror("Allocation ERROR");
		else
			perror(error_str);
		exit(EXIT_FAILURE);
	}
}

void	ft_chk_n_exit_if_null_pchar(char *str, char *error_str)
{
	if (str == NULL)
	{
		if (error_str == NULL)
			perror("Allocation ERROR");
		else
			perror(error_str);
		exit(EXIT_FAILURE);
	}
}

int	ft_matrix_get_num_col(char **matrix)
{
	int	col_num;

	col_num = -1;
	while (matrix[++col_num] != NULL)
		;
	return (col_num);
}

char	**ft_matrix_dup(char **matrix, int push)
{
	int		col_num;
	char	**list;
	int		i;

	list = NULL;
	col_num = ft_matrix_get_num_col(matrix);
	list = ft_realloc(list, (col_num + 1 + push) * sizeof(char *));
	ft_chk_n_exit_if_null_ppchar(list, NULL);
	i = -1;
	while (++i < col_num)
	{
		list[i] = ft_strdup(matrix[i]);
		ft_chk_n_exit_if_null_pchar(list[i], NULL);
	}
	list[i + push] = NULL;
	return (list);
}

char	**ft_matrix_push(char **matrix, char *str)
{
	int		col_num;
	char	**list;

	col_num = ft_matrix_get_num_col(matrix);
	list = ft_matrix_dup(matrix, 1);
	list[col_num] = ft_strdup(str);
	ft_chk_n_exit_if_null_pchar(list[col_num], NULL);
	ft_matrix_free(matrix);
	return (list);
}

void	ft_matrix_free(char **matrix)
{
	int	col_num;

	col_num = 0;
	if (matrix[0] != NULL)
	{
		while (matrix[col_num] != NULL)
		{
			free(matrix[col_num]);
			col_num++;
		}
		free(matrix[col_num]);
	}
	free(matrix);
}

char	**ft_matrix_remove_col_by_index(char **matrix, int index)
{
	int		col_num;
	char	**list;
	int		i;
	int		j;

	list = NULL;
	col_num = ft_matrix_get_num_col(matrix);
	list = ft_realloc(list, (col_num) * sizeof(char *));
	ft_chk_n_exit_if_null_ppchar(list, NULL);
	i = 0;
	j = 0;
	while (i < col_num - 1)
	{
		if (i == index)
			i++;
		list[j] = ft_strdup(matrix[i]);
		ft_chk_n_exit_if_null_pchar(list[j], NULL);
		i++;
		j++;
	}
	list[j] = NULL;
	ft_matrix_free(matrix);
	return (list);
}

void	ft_print_matrix_add_str2line_start(char **matrix, char *str, char *glue)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		if (matrix[i][0] == '?' && matrix[i][1] == '=')
		{
			i++;
			continue ;
		}
		ft_putstr_fd(str, 1);
		if (glue != NULL)
			ft_putstr_fd(glue, 1);
		ft_putstr_fd(matrix[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return ;
}

void	ft_swap2str(char **str1, char **str2)
{
	char	*tmp_str;

	tmp_str = ft_strdup(*str1);
	free(*str1);
	*str1 = ft_strdup(*str2);
	free(*str2);
	*str2 = ft_strdup(tmp_str);
	free(tmp_str);
}
