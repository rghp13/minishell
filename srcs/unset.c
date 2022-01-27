#include "minishell.h"

int	builtin_unset(char **argv, t_cont *cont)
{
	int	i;

	i = 1;
	if (argv == NULL)
		return (0);
	while (argv[i])
		remove_env(cont->env, argv[i++]);
	return (0);
}
