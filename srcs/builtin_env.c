#include "minishell.h"

int	builtin_env(char **argv, t_cont *cont)
{
	int	i;

	i = 0;
	(void)argv;
	while (cont->envstr[i])
		ft_printf("%s\n", cont->envstr[i++]);
	return (0);
}
