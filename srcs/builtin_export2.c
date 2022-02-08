#include "minishell.h"

/*
**only triggers if no argument
*/
void	export_p(int i, t_cont *cont)
{
	t_env *hold;

	if (i != 1)
		return ;
	hold = cont->env;
	while (hold)
	{
		ft_printf("declare -x %s=\"%s\"\n", hold->key, hold->value);
		hold = hold->next;
	}
}