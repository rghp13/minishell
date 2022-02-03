#include "../includes/minishell.h"

int	exec_bultin_bin_bridge(t_cmd *cmd, t_cont *cont)
{
	if (check_builtin(cmd->arg[0]) == 1)
		run_builtin(cmd, cont);
	else
		exec_cmd(cmd, cont);
	return (0);
}
