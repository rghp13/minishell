/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:03:26 by rponsonn          #+#    #+#             */
/*   Updated: 2022/02/17 14:20:25 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_lvl(t_cont *cont)
{
	t_env	*hold;
	char	*ptr;

	hold = find_env("SHLVL", cont->env);
	if (hold)
	{
		if (ft_atoi(hold->value) < 0 || !ft_isdigit(hold->value[0]))
			ptr = ft_itoa(0);
		else
			ptr = ft_itoa(ft_atoi(hold->value) + 1);
		if (ptr)
		{
			free(hold->value);
			hold->value = ptr;
		}
		else
			ft_putstr_fd("Malloc Error\n", STDERR_FILENO);
	}
	else
	{
		hold = add_env("SHLVL", "0", cont);
		add_last(cont->env, hold);
		if (cont->env == NULL)
			hold = hold->cont->env;
	}
}

/*~+ uses env variables PWD
**~- uses env variables OLDPWD
**~ doesn't use $HOME
**~romain if /home/romain exists return that
*/
char	*expand_tilde(const char *key, t_cont *cont)
{
	int		len;
	char	*str;

	len = ft_strlen(key);
	if (!key || !cont)
		return (NULL);
	if (key[0] != '~')
		str = NULL;
	else if (len == 1)
		str = get_tilde(cont, "$HOME");
	else if (len == 2 && key[1] == '+')
		str = get_tilde(cont, "$PWD");
	else if (len == 2 && key[1] == '-')
		str = get_tilde(cont, "$OLDPWD");
	else
		str = user_tilde(key);
	if (!str)
		return (ft_strdup(key));
	return (str);
}

char	*get_tilde(t_cont *cont, const char *envar)
{
	char	*hold;

	hold = get_key_val(envar, cont->env);
	return (hold);
}

char	*user_tilde(const char *key)
{
	char	*hold;

	key++;
	if (ft_strlen(key) < 2)
		return (NULL);
	hold = ft_strjoin("/home/", key);
	if (!hold)
		return (NULL);
	if (access(hold, F_OK) == 0)
		return (hold);
	free(hold);
	return (NULL);
}
