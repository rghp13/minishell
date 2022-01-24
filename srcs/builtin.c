#include "minishell.h"

int	check_builtin(const char *cmd)
{
	if (cmd == NULL)
		return (-1);
	if (ft_stringcomp(cmd, "echo") == 0 || ft_stringcomp(cmd, "cd") == 0 || \
	ft_stringcomp(cmd, "pwd") == 0 || ft_stringcomp(cmd, "export") == 0 || \
	ft_stringcomp(cmd, "unset") == 0 || ft_stringcomp(cmd, "env") == 0 || \
	ft_stringcomp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}