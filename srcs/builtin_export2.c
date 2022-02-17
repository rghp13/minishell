/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:58:07 by rponsonn          #+#    #+#             */
/*   Updated: 2022/02/17 03:51:22 by romain           ###   ########.fr       */
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
