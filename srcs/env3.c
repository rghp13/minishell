#include "minishell.h"

/*
**don't need update_envstr because it's being made on the next function
**TEST THIS ONCE YOU CAN DO RELATIVE EXECUTION
*/
void	shell_lvl(t_cont *cont)
{
	t_env	*hold;
	int		lvl;
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
	}
}
