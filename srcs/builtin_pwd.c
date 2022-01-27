#include "minishell.h"

int	builtin_pwd(char **argv, t_cont *cont)
{
	char	*val;

	(void)argv;
	val = getcwd(NULL, 0);
	if (val == NULL)
	{
		val = get_key_val("$PWD", cont->env);
		if (val == NULL)
		{
			ft_printf("Unable to find current directory\n");
			return (1);
		}
	}
	ft_printf("%s\n", val);
	return (0);
}
