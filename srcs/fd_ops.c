/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:25:03 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 02:25:04 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fd_reset(t_cont *cont)
{
	dup2(cont->fd_in_perm, 0);
	dup2(cont->fd_out_perm, 1);
}

void	fd_close(t_cont *cont)
{
	if (cont->fd_in > 0)
		close(cont->fd_in > 0);
	if (cont->fd_out)
		close(cont->fd_out);
	if (cont->pipefd[0] > 0)
		close(cont->pipefd[0]);
	if (cont->pipefd[1] > 0)
		close(cont->pipefd[1]);
}

void	fd_zero(t_cont *cont)
{
	cont->fd_in = -1;
	cont->fd_out = -1;
	cont->pipefd[0] = -1;
	cont->pipefd[1] = -1;
}

void	fd_inits(t_cont *cont)
{
	cont->fd_in_perm = dup(0);
	cont->fd_out_perm = dup(1);
	fd_zero(cont);
}
