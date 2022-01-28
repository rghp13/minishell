#include "minishell.h"

int	builtin_pwd(char **argv, t_cont *cont)
{
	char	val[PATH_MAX];

	(void)argv;
	(void)cont;
	if (getcwd(val, PATH_MAX))
	{
		ft_printf("%s\n", val);
		return (0);
	}
	return (1);
}
