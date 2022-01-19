#include "minishell.h"

/*
**export returns 1 only if key has any symbol that isn't =
**even with that the program keeps going
**
**
*/

int	builtin_export(char **argv, t_cont *cont)
{
	int		i;
	t_env	*new_env;
	int		flag;
	char	**split;

	i = -1;
	flag = 0;
	while (argv[++i])
	{
		if (check_valid_export(argv[i], cont) == 0)
			continue ;
		new_env = ft_calloc(1, sizeof(t_env));
		if (new_env == NULL || assign_env_to_struct(new_env, argv[i]))//test this
		{
			free_envp(new_env, NULL);
			return (1);
		}
		add_last(cont->env, new_env);
	}
	split = output_env_array(cont->env);
	if (split == NULL)
		return (1);
	ft_free_all_split(cont->envstr);
	cont->envstr = split;
	return (flag);
}

int	check_valid_export(const char *str, t_cont *cont)
{
	int	i;
	strchr()
	
}
