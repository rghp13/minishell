#include "minishell.h"

/*
**don't need update_envstr because it's being made on the next function
**TEST THIS ONCE YOU CAN DO RELATIVE EXECUTION
*/
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
//~+ uses env variables PWD
//~- uses env variables OLDPWD
//~ doesn't use $HOME
//~romain if /home/romain exists return that
char	*expand_tilde(const char *key, t_cont *cont)
{
	int		len;
	char	*str;

	len = ft_strlen(key);
	if (!key || !cont)
		return (NULL);
	if (key[0] != '~')
		;//in case this isn't a ~ just strdup and return
	else if (len == 1)
		str = get_tilde(cont, "$HOME");
	else if (len == 2 && key[1] == '+')
		str = get_tilde(cont, "$PWD");
	else if (len == 2 && key[1] == '-')
		str = get_tilde(cont, "$OLDPWD");
	else
		str = user_tilde(key, cont);
	if (!str)
		return (ft_strdup(key));
	return (str);
}

char	*get_tilde(t_cont *cont, const char *envar)
{
	char	*str;
	char	*hold;

	hold = get_key_val(envar, cont->env);
	if (hold)
	{
		str = ft_strjoin(hold, "/");
		free(hold);
		return (str);
	}
	return (NULL);
}

char	*user_tilde(const char *key ,t_cont *cont)
{
	char	*hold;

	key++;
	if (ft_strlen(key) < 2)//should have triggered get_tilde prior
		return (NULL);
	hold = ft_strjoin("/home/", key);
	if (!hold)
		return (NULL);
	if (access(hold, F_OK) == 0)
		return (hold);
	free(hold);
	return (NULL);
}