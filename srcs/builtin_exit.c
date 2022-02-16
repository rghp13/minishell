/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:56:55 by rponsonn          #+#    #+#             */
/*   Updated: 2022/02/16 22:55:27 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	builtin_exit(char **argv, t_cont *cont)
{
	uint8_t	ret;

	ret = cont->exit_status;
	if (cont->cmd->next == NULL)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("bash: exit: too many agruments\n", STDERR_FILENO);
		return (1);
	}
	else if (argv[1])
	{
		if (!ft_strisnum(argv[1]))
			ret = exit_error(argv[1]);
		else
			ret = ft_atoi(argv[1]);
	}
	if (cont->cmd->next == NULL)
		cont->exit_flag = 1;
	return (ret);
}

uint8_t	exit_error(const char *str)
{
	ft_putstr_fd("bash: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	return (2);
}
