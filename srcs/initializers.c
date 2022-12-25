/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:19:38 by vrubio            #+#    #+#             */
/*   Updated: 2022/12/25 18:04:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_inicialize_vars(t_vars *vars)
{
	vars->i = 0;
	vars->j = 0;
	vars->k = 0;
	vars->l = 0;
	vars->m = 0;
	vars->start = 0;
	vars->end = 0;
	vars->size = 0;
	vars->inner_quote = 0;
	vars->outer_quote = 0;
	vars->str = NULL;
	vars->str2 = NULL;
	vars->tmp_str = NULL;
	vars->tmp_str2 = NULL;
	vars->matrix = NULL;
	vars->matrix2 = NULL;
	vars->tmp_matrix = NULL;
	vars->tmp_matrix2 = NULL;
	vars->p2p2p = NULL;
}

t_cmd	*ft_inicialize_cmd(char **matrix)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->type = NADA;
	cmd->file = NULL;
	cmd->file_in = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->flag = 0;
	cmd->fd_in = 0;
	cmd->args = malloc((1 + ft_matrix_get_num_col(matrix)) * sizeof(char **));
	return (cmd);
}
