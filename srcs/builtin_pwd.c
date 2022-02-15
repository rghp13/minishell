/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:00:39 by rponsonn          #+#    #+#             */
/*   Updated: 2022/02/15 19:00:41 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **argv, t_cont *cont)
{
	char	*val;

	(void)argv;
	(void)cont;
	errno = 0;
	val = getcwd(NULL, 0);
	if (val)
	{
		ft_printf("%s\n", val);
		free(val);
		return (0);
	}
	if (cont->pwd)
	{
		ft_printf("%s\n", cont->pwd);
		return (0);
	}
	else
		perror("pwd");
	return (1);
}
