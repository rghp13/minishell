/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:58:07 by rponsonn          #+#    #+#             */
/*   Updated: 2022/02/15 19:00:29 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
**only triggers if no argument
*/
void	export_p(int i, t_cont *cont)
{
	t_env	*hold;

	if (i != 1)
		return ;
	hold = cont->env;
	while (hold)
	{
		ft_printf("declare -x %s=\"%s\"\n", hold->key, hold->value);
		hold = hold->next;
	}
}
