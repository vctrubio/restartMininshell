/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:31 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/12/22 15:19:32 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_concat3(char *s1, char *s2, char *s3)
{
	char	**matrix;
	char	*str;

	matrix = NULL;
	matrix = ft_realloc(matrix, 4 * sizeof(char *));
	matrix[0] = ft_strdup(s1);
	matrix[1] = ft_strdup(s2);
	matrix[2] = ft_strdup(s3);
	matrix[3] = NULL;
	str = ft_concat_multi(matrix, NULL);
	ft_matrix_free(matrix);
	return (str);
}

char	*ft_concat_string_between_chars(char c_start, char *s, char c_end)
{
	char	*str;
	char	s_start[2];
	char	s_end[2];

	s_start[0] = c_start;
	s_start[1] = '\0';
	s_end[0] = c_end;
	s_end[1] = '\0';
	str = ft_concat3(s_start, s, s_end);
	return (str);
}

char	*ft_concat_multi_getsize_n_alloc(char **s, char *glue)
{
	int		str_len;
	int		i;
	char	*str;

	str = NULL;
	str_len = 0;
	i = 0;
	while (s[i] != NULL)
	{
		str_len += ft_strlen(s[i]);
		if (glue != NULL && s[i + 1] != NULL)
			str_len += 2 * ft_strlen(glue);
		i++;
	}
	str = ft_realloc(str, (str_len + 1) * sizeof(char));
	ft_bzero(str, str_len + 1);
	return (str);
}

char	*ft_concat_multi(char **s, char *glue)
{
	int		i;
	int		position;
	char	*str;
	int		block_len;

	str = ft_concat_multi_getsize_n_alloc(s, glue);
	i = 0;
	position = 0;
	block_len = 0;
	while (s[i] != NULL)
	{
		block_len = ft_strlen(s[i]);
		ft_memmove(str + position, s[i], block_len);
		position += block_len;
		if (s[i + 1] != NULL && glue != NULL)
		{
			ft_memmove(str + position, glue, ft_strlen(glue));
			position += ft_strlen(glue);
		}
		i++;
	}
	return (str);
}
