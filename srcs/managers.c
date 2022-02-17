/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:45:47 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 15:22:39 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parsing_manager(char *parsed_line, t_cont *cont)
{
	int	val;

	if (syntax_check(parsed_line, cont))
		return (-1);
	if (parse_command(parsed_line, &cont->cmd))
	{
		ft_putstr_fd(PARSEERR, STDERR_FILENO);
		cont->exit_status = 1;
		return (-1);
	}
	if (substitute_variables(cont))
	{
		ft_putstr_fd(VARERR, STDERR_FILENO);
		cont->exit_status = 1;
		return (-1);
	}
	val = argv_loop(cont);
	if (val)
	{
		if (val == -2)
			ft_putstr_fd(FILEERR, STDERR_FILENO);
		cont->exit_status = 1;
		return (-1);
	}
	return (0);
}

int	execution_manager(t_cont *cont)
{
	int	value;

	value = exec_main(cont);
	while (wait(NULL) > 0)
		;
	if (value == -1)
	{
		ft_putstr_fd(EXECERR, STDERR_FILENO);
		cont->exit_status = 1;
	}
	else if (value == -2)
	{
		ft_putstr_fd(FILEERR, STDERR_FILENO);
		cont->exit_status = 1;
	}
	fd_close(cont);
	fd_reset(cont);
	return (value);
}
