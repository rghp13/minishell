/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:53:55 by rponsonn          #+#    #+#             */
/*   Updated: 2022/02/17 02:23:25 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **argv, t_cont *cont)
{
	int	ret;

	ret = 0;
	if (argv[1] == NULL)
	{
		ret = go_home(cont);
	}
	else if (argv[2])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", STDERR_FILENO);
		ret = 1;
	}
	else if (ft_stringcomp("-", argv[1]) == 0)
		ret = dir_swap(cont);
	else
	{
		ret = chdir(argv[1]);
		if (ret)
		{
			perror("cd");
			return (1);
		}
		update_pwd_env(cont, NULL);
	}
	return (ret);
}

int	dir_swap(t_cont *cont)
{
	t_env	*old;

	old = find_env("OLDPWD", cont->env);
	if (!old || !old->value)
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(old->value) == -1)
	{
		perror("cd");
		return (1);
	}
	ft_printf("%s\n", old->value);
	update_pwd_env(cont, NULL);
	return (0);
}

int	go_home(t_cont *cont)
{
	t_env	*ptr;

	ptr = find_env("HOME", cont->env);
	if (!ptr)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(ptr->value) == -1)
	{
		perror("cd");
		return (1);
	}
	update_pwd_env(cont, NULL);
	return (0);
}

void	update_pwd_env(t_cont *cont, char *ptr)
{
	t_env	*hold;

	remove_env(cont->env, "OLDPWD");
	hold = find_env("PWD", cont->env);
	if (hold)
	{
		ptr = ft_strdup("OLDPWD");
		if (!ptr)
		{
			perror("cd");
			return ;
		}
		free(hold->key);
		hold->key = ptr;
	}
	ptr = getcwd(NULL, 0);
	if (ptr)
	{
		hold = add_env("PWD", ptr, cont);
		if (hold)
			add_last(cont->env, hold);
		free(cont->pwd);
		cont->pwd = ptr;
	}
	update_envstr(cont);
}
