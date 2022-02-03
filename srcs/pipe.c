#include "../includes/minishell.h"

int	pipe_execution(t_cmd *cmd, t_cmd *cmd2, t_cont *cont)
{
	int	pipefd[2];
	
	if (pipe(pipefd))
		return (-1);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	if (check_builtin(cmd->arg[0]) == 1)
		run_builtin(cmd, cont);
	else
		exec_cmd(cmd, cont);
	cmd = cmd->pipechain;
	while (cmd->next)
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		if (pipe(pipefd))
			return (-1);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		if (check_builtin(cmd->arg[0]) == 1)
			run_builtin(cmd, cont);
		else
			exec_cmd(cmd, cont);
		cmd = cmd->next;
	}
	dup2(cont->fd_out_perm, 1);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	if (check_builtin(cmd->arg[0]) == 1)
		run_builtin(cmd, cont);
	else
		exec_cmd(cmd, cont);
	fd_reset(cont);
	return (0);
}