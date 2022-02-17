/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:58:43 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 02:58:56 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ret_path_split(t_env *env)
{
	char	*bin;
	char	**split;

	bin = get_key_val("$PATH", env);
	if (!bin)
		return (NULL);
	split = ft_split(bin, ':');
	free(bin);
	return (split);
}
//you are able to /bin/echo when you have no idea where you are
//

char	*find_relative_path(const char *str, t_cont *cont)
{
	char	*hold;
	char	*hold2;

	if (!str || !str[0])
		return (NULL);
	if (str[0] == '/')
	{
		if (access(str, F_OK) == 0)
			return (strdup(str));
		return (NULL);
	}
	if (cont->pwd)
	{
		hold = ft_strjoin(cont->pwd, "/");
		if (hold == NULL)
			return (NULL);
		hold2 = ft_strjoin(hold, str);
		free(hold);
		return (hold2);
	}
	ft_putstr_fd("error retrieving currentdirectory: cannot access parent directories: \
	No such file or directory\n", STDERR_FILENO);
	return (NULL);
}

char	*get_abs_path(const char *src, t_env *env)
{
	char	*bin;
	char	**split;
	int		i;

	i = -1;
	if (ft_strchr(src, '/'))
		return (find_relative_path(src, env->cont));
	split = ret_path_split(env);
	if (split == NULL)
		return (NULL);
	while (split[++i])
	{
		if (merge_path_name(&split[i], src) != 0)
			return ((void *)(uintptr_t)ft_free_all_split(split));
		if (access(split[i], F_OK) != -1)
		{
			bin = ft_strdup(split[i]);
			ft_free_all_split(split);
			return (bin);
		}
	}
	ft_free_all_split(split);
	return (NULL);
}

int	merge_path_name(char **path, const char *name)
{
	char	*hold;
	char	*hold2;

	if (*path == NULL)
		return (1);
	hold = ft_strjoin(*path, "/");
	if (hold == NULL)
		return (1);
	hold2 = ft_strjoin(hold, name);
	free(hold);
	if (hold2 == NULL)
		return (1);
	free(*path);
	*path = hold2;
	return (0);
}

int	list_get_path(t_cmd *cmd, t_env *env)
{
	while (cmd)
	{
		relative_path_bridge(cmd, env);
		cmd = cmd->next;
	}
	return (0);
}
