/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:59:10 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 03:44:17 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	relative_path_bridge(t_cmd *cmd, t_env *env)
{
	int	len;

	len = ft_strlen(cmd->arg[0]);
	if (len >= 2 && cmd->arg[0][0] == '.' && cmd->arg[0][1] == '/')
		cmd->abspath = ft_strdup(cmd->arg[0]);
	else
	{
		cmd->abspath = get_abs_path(cmd->arg[0], env);
	}
	return (0);
}

int	err_ret_value(int erno, t_cmd *cmd)
{
	if (cmd->abspath == NULL && access(cmd->arg[0], F_OK) == 0)
	{
		if (access(cmd->arg[0], X_OK))
			return (126);
	}
	if (cmd->abspath == NULL)
		return (127);
	if (erno == 13)
		return (126);
	return (1);
}

void	error_status(t_cont *cont)
{
	perror("Bash");
	cont->exit_status = 1;
	return ;
}
