/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:57:52 by rponsonn          #+#    #+#             */
/*   Updated: 2022/02/16 20:06:34 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**export returns 1 only if key has any symbol that isn't =
**even with that the program keeps going
** ! error starts from ! till end of string//not implementing
** # is taken as a comment so anything after it is ignored
** & - cause errors
** _ is accepted do not return error
**export PWD=$HOME becomes PWDHOME
*/

int	builtin_export(char **argv, t_cont *cont)
{
	t_export	exp;

	exp.i = 0;
	exp.flag = 0;
	while (argv[++exp.i])
	{
		if (check_valid_export(argv[exp.i], &exp.flag) == 0)
			continue ;
		exp.new_env = find_env(argv[exp.i], cont->env);
		if (exp.new_env == NULL)
			create_new_env(argv[exp.i], cont);
		else
		{
			if (exp.new_env->value)
				free(exp.new_env->value);
			exp.new_env->value = ft_strdup(ft_strchr(argv[exp.i], '=') + 1);
		}
	}
	exp.split = output_env_array(cont->env);
	if (exp.split == NULL)
		return (1);
	ft_free_all_split(cont->envstr);
	cont->envstr = exp.split;
	export_p(exp.i, cont);
	return (exp.flag);
}

void	create_new_env(char *argv, t_cont *cont)
{
	t_env	*new_env;

	if (argv == NULL || cont == NULL)
		return ;
	new_env = ft_calloc(1, sizeof(t_env));
	if (new_env == NULL || assign_env_to_struct(new_env, argv))
	{
		free_envp(new_env, NULL);
		return ;
	}
	new_env->cont = cont;
	add_last(cont->env, new_env);
}

/*
**0 means skip
*/
int	check_valid_export(const char *str, int *flag)
{
	int		i;
	int		c;
	char	*ptr;

	ptr = ft_strchr(str, '=');
	i = 0;
	if (ptr == str || str[0] == '\0')
	{
		*flag = 1;
		return (export_error(str));
	}
	if (ptr == NULL)
		return (0);
	c = ptr - str;
	while (i < c)
	{
		if (ft_isasymbol(str[i]) == 1 || ft_isdigit(str[0]) || str[i] == ' ')
		{
			*flag = 1;
			return (export_error(str));
		}
		i++;
	}
	return (1);
}

int	export_error(const char *str)
{
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (0);
}

/*
**returns 1 if symbol
**except _
*/
int	ft_isasymbol(const char str)
{
	if (str == '_')
		return (0);
	if (str >= '!' && str < '0')
		return (1);
	else if (str >= ':' && str < 'A')
		return (1);
	else if (str >= '[' && str < 'a')
		return (1);
	else if (str >= '{' && str <= '~')
		return (1);
	else
		return (0);
}
