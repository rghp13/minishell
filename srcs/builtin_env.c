/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:56:33 by rponsonn          #+#    #+#             */
/*   Updated: 2022/02/15 18:56:36 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **argv, t_cont *cont)
{
	int	i;

	i = 0;
	(void)argv;
	while (cont->envstr[i])
		ft_printf("%s\n", cont->envstr[i++]);
	return (0);
}
