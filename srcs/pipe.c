#include "../includes/minishell.h"

int	pipe_start(t_cmd *cmd, t_cont *cont)
{
	if (pipe(cont->pipefd))
		return (-1);
	dup2(cont->pipefd[1], 1);
	close(cont->pipefd[1]);
	if (prepare_redirection(cmd, cont))
		return (-2);
	exec_bultin_bin_bridge(cmd, cont);
	return (0);
}

int	pipe_middle(t_cmd *cmd, t_cont *cont)
{
	dup2(cont->pipefd[0], 0);
	close(cont->pipefd[0]);
	if (pipe(cont->pipefd))
		return (-1);
	dup2(cont->pipefd[1], 1);
	close(cont->pipefd[1]);
	if (prepare_redirection(cmd, cont))
		return (-2);
	exec_bultin_bin_bridge(cmd, cont);
	return (0);
}

int	pipe_end(t_cmd *cmd, t_cont *cont)
{
	dup2(cont->fd_out_perm, 1);
	dup2(cont->pipefd[0], 0);
	close(cont->pipefd[0]);
	if (prepare_redirection(cmd, cont))
		return (-2);
	exec_bultin_bin_bridge(cmd, cont);
	cont->child_pid = 1;
	fd_reset(cont);
	while (wait(NULL) > 0)
		;
	cont->child_pid = 0;
	return (0);
}

int	pipe_execution(t_cmd *cmd, t_cont *cont)
{
	int	val;

	val = pipe_start(cmd, cont);
	cmd = cmd->next;
	if (val)
		return (val);
	while (cmd->next)
	{
		val = pipe_middle(cmd, cont);
		cmd = cmd->next;
	}
	if (val)
		return (val);
	return (pipe_end(cmd, cont));
}