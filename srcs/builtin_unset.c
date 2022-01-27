#include "minishell.h"

int	builtin_unset(char **argv, t_cont *cont)
{
	int		i;
	char	**split;

	i = 1;
	if (argv == NULL)
		return (0);
	while (argv[i])
		remove_env(cont->env, argv[i++]);
	split = output_env_array(cont->env);
	if (split == NULL)
		return (1);
	ft_free_all_split(cont->envstr);
	cont->envstr = split;
	return (0);
}
