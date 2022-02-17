/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:47:56 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 16:45:03 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_singals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	return ;
}

void	signal_handler(int signal)
{
	signal_redirector(NULL, signal, 0);
	return ;
}

int	signal_redirector(t_cont *ptr, int signal, int mode)
{
	static t_cont	*cont;

	if (mode)
		cont = ptr;
	if (signal == SIGINT && !cont->child_pid)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT && !cont->child_pid)
		return (0);
	else if (cont->child_pid > 0)
	{
		kill(cont->child_pid, signal);
		if (signal == SIGQUIT)
			ft_putstr_fd("Quit\n", STDERR_FILENO);
	}
	return (0);
}
