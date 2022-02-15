/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:00:49 by rponsonn          #+#    #+#             */
/*   Updated: 2022/02/15 19:00:50 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv, t_cont *cont)
{
	int		i;
	char	**split;

	i = 1;
	if (argv == NULL)
		return (0);
	while (argv[i])
		remove_env(cont->env, argv[i++]);
	split = output_env_array(cont->env);
	if (split == NULL)
		return (1);
	ft_free_all_split(cont->envstr);
	cont->envstr = split;
	return (0);
}
