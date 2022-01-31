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
	else
	{
		ret = chdir(argv[1]);
		if (ret)
			return (cd_error_print(argv[1]));
		update_pwd_env(cont, NULL);
	}
	return (ret);
}

int	go_home(t_cont *cont)
{
	char	*ptr;
	int		ret;

	ptr = get_key_val("$HOME", cont->env);
	if (!ptr)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	ret = chdir(ptr);
	if (ret)
		return (cd_error_print(ptr));
	update_pwd_env(cont, NULL);
	return (0);
}

int	cd_error_print(const char *str)
{
	ft_putstr_fd("bash: cd: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (1);
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
			ft_putstr_fd("Malloc Error: Failed to Update env\n", STDERR_FILENO);
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
		else
			free(ptr);
	}
	update_envstr(cont);
}
