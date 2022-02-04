#include "minishell.h"

int	builtin_echo(char **argv, t_cont *cont)
{
	int	n;
	int	flag;
	int	i;

	i = 1;
	n = 0;
	flag = 0;
	(void)cont;
	if (argv[i] && ft_stringcomp("-n", argv[i]) == 0)
	{
		n = 1;
		if (argv[++i] == NULL)
			return (0);
	}
	while (argv[i])
	{
		if (flag == 0)
			flag++;
		else
			write(STDOUT_FILENO, " ", 1);
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
	}
	if (n == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
