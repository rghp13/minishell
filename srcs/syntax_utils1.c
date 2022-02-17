/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:49:12 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 02:53:13 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var_exist(char *cmd, t_env *env, int j)
{
	int		ret;
	char	*key;
	char	*val;

	ret = 0;
	key = get_var_name(&cmd[j]);
	val = get_key_val(key, env);
	if (!ft_strlen(val))
		ret = 1;
	free(key);
	free(val);
	return (ret);
}
