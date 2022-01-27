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

void	run_builtin(t_cmd *cmd, t_cont *cont)
{
	if (ft_stringcomp(cmd->arg[0], "echo") == 0)
		printf("entered echo\n");
	else if (ft_stringcomp(cmd->arg[0], "cd") == 0)
		printf("entered cd\n");
	else if (ft_stringcomp(cmd->arg[0], "pwd") == 0)
		printf("entered pwd\n");
	else if (ft_stringcomp(cmd->arg[0], "export") == 0)
		cont->exit_status = builtin_export(cmd->arg, cont);
	else if (ft_stringcomp(cmd->arg[0], "unset") == 0)
		cont->exit_status = builtin_unset(cmd->arg, cont);
	else if (ft_stringcomp(cmd->arg[0], "env") == 0)
		cont->exit_status = builtin_env(cmd->arg, cont);
	else if (ft_stringcomp(cmd->arg[0], "exit") == 0)
		printf("entered exit\n");
	return ;
}
