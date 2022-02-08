#include "../includes/minishell.h"

int	pipe_execution(t_cmd *cmd, t_cont *cont)
{
	if (pipe(cont->pipefd))
		return (-1);
	dup2(cont->pipefd[1], 1);
	close(cont->pipefd[1]);
	if (prepare_redirection(cmd, cont))
		return (-1);
	exec_bultin_bin_bridge(cmd, cont);
	cmd = cmd->pipechain;
	while (cmd->next)
	{
		dup2(cont->pipefd[0], 0);
		close(cont->pipefd[0]);
		if (pipe(cont->pipefd))
			return (-1);
		dup2(cont->pipefd[1], 1);
		close(cont->pipefd[1]);
		if (prepare_redirection(cmd, cont))
			return (-1);
		exec_bultin_bin_bridge(cmd, cont);
		cmd = cmd->next;
	}
	dup2(cont->fd_out_perm, 1);
	dup2(cont->pipefd[0], 0);
	close(cont->pipefd[0]);
	if (prepare_redirection(cmd, cont))
		return (-1);
	exec_bultin_bin_bridge(cmd, cont);
	return (0);
}